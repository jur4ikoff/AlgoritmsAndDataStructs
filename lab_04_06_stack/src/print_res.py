import pandas as pd
import os, sys

GREEN = "\033[0;32m"
RESET = "\033[0m"


def main():
    script_path = os.path.abspath(__file__)
    directory_path = os.path.dirname(script_path)

    if len(sys.argv) == 2:
        if sys.argv[1] == "a":
            pd.set_option("display.max_rows", None)

    memory_df = pd.read_csv(f"{directory_path}/../data/memory.csv", delimiter=";")
    speed_df = pd.read_csv(f"{directory_path}/../data/speed.csv", delimiter=";")

    print(
        GREEN,
        "Таблица зависимости памяти, занимаемой стеком каждого методом, от размера (байты)",
        RESET,
    )
    print(memory_df.head(10))
    print()

    print(
        GREEN,
        "Таблица зависимости времени выполнения каждого метода, от размера (наносекунды)",
        RESET,
    )
    print(speed_df.head(20))


if __name__ == "__main__":
    main()
