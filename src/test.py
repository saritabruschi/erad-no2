import os
import numpy as np 
import pandas as pd
import matplotlib.pyplot as plt


# testando a criação do data frame
column_names = ["a", "b", "c"]
df = pd.DataFrame(columns = column_names)
print(df.head(10))

x = {'a':133, 'b':222, 'c':2345}
df = df.append(x, ignore_index=True)
print(df.head(10))

