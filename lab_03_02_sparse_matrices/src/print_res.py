import pandas as pd
import os

# Получение пути к текущему скрипту
script_path = os.path.abspath(__file__)
# Получение директории, в которой находится скрипт
script_directory = os.path.dirname(script_path)
data_directory = f"{script_directory}/../data/"
csv_files = [file for file in os.listdir(data_directory) if file.endswith(".csv")]

memory_dataframes = []
speed_datafame = []
for file in csv_files:
    if file.startswith("memory"):
        full_path = os.path.join(data_directory, file)
        size = file.split(".")[0].split("_")[1]
        df = pd.read_csv(full_path, delimiter=";")
        df["size"] = size
        memory_dataframes.append(df)

    if file.startswith("matrix"):
        full_path = os.path.join(data_directory, file)
        size = file.split(".")[0].split("_")[1]
        df = pd.read_csv(full_path, delimiter=";")
        df["size"] = size
        speed_datafame.append(df)

memory_df = pd.concat(memory_dataframes, ignore_index=True)
speed_df = pd.concat(speed_datafame, ignore_index=True)
new_order = ["size", "fill", "def", "csc"]

memory_df = memory_df.reindex(columns=new_order)
speed_df = speed_df.reindex(columns=new_order)

memory_df['size'] = pd.to_numeric(memory_df['size'])
memory_df['fill'] = pd.to_numeric(memory_df['fill'])
memory_df = memory_df.sort_values(by=['size', "fill"], ascending=[True, True])
memory_df['result'] = memory_df['def'] / memory_df['csc']

speed_df['size'] = pd.to_numeric(speed_df['size'])
speed_df['fill'] = pd.to_numeric(speed_df['fill'])
speed_df = speed_df.sort_values(by=['size', "fill"], ascending=[True, True])
speed_df['result'] = speed_df['def'] / speed_df['csc']

print(memory_df)
print(speed_df)


memory_df.to_csv(f"{script_directory}/../memory.csv", sep=';', index=False)
speed_df.to_csv(f"{script_directory}/../speed.csv",  sep=';', index=False)
