import pandas as pd
import os
import fnmatch


# Получение пути к текущему скрипту
script_path = os.path.abspath(__file__)
# Получение директории, в которой находится скрипт
script_directory = os.path.dirname(script_path)
data_directory = f"{script_directory}/../data/"
csv_files = [file for file in os.listdir(data_directory) if file.endswith(".csv")]

memory_dataframes = []
for file in csv_files:
    if file.startswith("memory"):
        full_path = os.path.join(data_directory, file)
        size = file.split(".")[0].split("_")[1]
        df = pd.read_csv(full_path, delimiter=";")
        df["size"] = size
        memory_dataframes.append(df)

memory_df = pd.concat(memory_dataframes, ignore_index=True)
new_order = ["size", "fill", "def", "csc"]

memory_df = memory_df.reindex(columns=new_order)
memory_df = memory_df.sort_values(by='size')
print(memory_df)
