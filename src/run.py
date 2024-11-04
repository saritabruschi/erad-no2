import os, math
import subprocess
import numpy as np 
import pandas as pd
import matplotlib.pyplot as plt

NUM_EXPERIMENTS = 15

def perf_exec(opt, val, id):
    file_name = 'results/raw/exp_n{}_{}_{}.txt'.format(id, opt, val)
    print("[+] Executando[{}]: Modo[{}] Tamanho[{}]...".format(id, opt, val))
    os.system('sudo perf stat -o {} -e L1-dcache-loads,L1-dcache-load-misses,branches,branch-misses ./exec {} {}'.format(file_name, val, opt))

def exportar_resultados():
    options = ['i', 'u'] 
    values  = [10, 100, 1000]

    for opt in options:
        for val in values:
            for id in range(1, NUM_EXPERIMENTS+1):
                perf_exec(opt, val, id)


def preproccess_file(opt, val, id):
    data  = { 'N':int(val), 'option':opt }
    
    f     = open('results/raw/exp_n{}_{}_{}.txt'.format(id, opt, val))
    lines = f.readlines()
    for l in lines:
        if 'L1-dcache-load-misses' in l:
            l = l.strip().split()
            data['L1-misses-raw'] = float(l[0].replace('.', ''))
            data['L1-misses']     = float(l[3].replace(',', '.').replace('%',''))
        elif 'L1-dcache-loads' in l:
            l = l.strip().split()
            data['L1-loads'] = float(l[0].replace('.', ''))
        elif 'branch-misses' in l:
            l = l.strip().split()
            data['branch-misses-raw'] = float(l[0].replace('.', ''))
            data['branch-misses'] = float(l[3].replace(',', '.').replace('%',''))
        elif 'branches' in l:
            l = l.strip().split()
            data['branches'] = float(l[0].replace('.', ''))
    f.close()

    #print(data)
    return data

def preproccess_data():
    options = ['i', 'u'] 
    values  = [10, 100, 1000]
    NUM_EXPERIMENTS = 15

    # Criando o DataFrame a ser populado
    column_names = ['N', 'option', 'L1-loads', 'L1-misses-raw', 'L1-misses', 'branches', 'branch-misses-raw', 'branch-misses']
    df = pd.DataFrame(columns = column_names)

    for opt in options:
        for val in values:
            for id in range(1, NUM_EXPERIMENTS+1):
                data = preproccess_file(opt, val, id)
                df = df.append(data, ignore_index=True)

    return df


def processs_resultados(df):
    # df_i_10    = df[ (df['N'] == 10)    & (df['option'] == 'i')]
    
    options = ['i', 'u'] 
    values  = [10, 100, 1000]
    metrics = ['L1-loads', 'L1-misses-raw', 'L1-misses', 'branches', 'branch-misses-raw', 'branch-misses']

    # 1º - Gerando Box plot dos gráficos de maneira simples e calculando o intervalo de confiança 
    for opt in options:
        str_option = 'Interchange' if (opt == 'i') else 'Unroll'
        print("[+] Gerando Imagens para Loop {}".format(str_option))
        
        for val in values:
            temp_df = df[ (df['N'] == val) & (df['option'] == opt)]
            for c in metrics:
                # Calculando o intervalo de confiança à 95% com t-student
                conf_interval = (2.5096 * temp_df[c].std()) / math.sqrt(float(val))

                plt.figure()
                plt.title("Loop {} n={}  {}=({:.2f} + {:.2f})".format(str_option, val, c, temp_df[c].mean(), conf_interval ))
                temp_df.boxplot(column=c)
                #plt.show()
                plt.savefig('results/images/exp_n{}_{}_{}.txt.'.format(val, opt, c))
                plt.close('all') #impedindo de abrir muitas figuras simultaneamente
    
    # 2º gerando Gráficos para comparar as métricas
    for val in values:
        temp_df = df[ (df['N'] == val)]
        for c in metrics:
            temp_df.boxplot(column=c, by=['N','option'])
            plt.savefig('results/comparisons/cmp_n{}_{}.txt.'.format(val, c))
            plt.close('all')

if __name__ == '__main__':
    print("[+] Iniciando experimentos no perf ({} repetições/configuração)...".format(NUM_EXPERIMENTS))
    exportar_resultados()
    print("[+] Experimentos finalizados.")
    
    print("[+] Iniciando pré-processamento...")
    df = preproccess_data()
    print("[+] Salvando resultados em disco (results/dataframe/df.csv)...")
    df.to_csv('results/dataframe/df.csv', index=False, header=True)
    print("[+] Resultados salvos em um Dataframe {}.".format(df.shape))

    print("[+] Iniciando Análise de dados....")
    processs_resultados(df)
    print("[+] Análise finalizada, encerrando processo.")