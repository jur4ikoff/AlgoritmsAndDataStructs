"""Скрипт для заполнения базы данных, для тестирования производительности"""

import os
import random
import string

russian_names = [
    "Александр",
    "Максим",
    "Дмитрий",
    "Сергей",
    "Михаил",
    "Андрей",
    "Иван",
    "Владимир",
    "Егор",
    "Роман",
    "Николай",
    "Григорий",
    "Артем",
    "Павел",
    "Виктор",
    "Тимур",
    "Олег",
    "Станислав",
    "Кирилл",
    "Денис",
]
russian_surnames = [
    "Иванов",
    "Петров",
    "Сидоров",
    "Кузнецов",
    "Смирнов",
    "Попов",
    "Зайцев",
    "Волков",
    "Белов",
    "Лебедев",
    "Новиков",
    "Морозов",
    "Фedorov",
    "Ковалев",
    "Александров",
    "Соколова",
    "Орлов",
    "Степанов",
    "Егоров",
    "Дмитриев",
]
gender = ["M", "F"]
modes = ["H", "R", "F"]
russian_street_names = [
    "Red Square",
    "Lenin Street",
    "Victory Avenue",
    "Gorky Street",
    "Pushkin Boulevard",
    "Tverskaya Street",
    "Soviet Avenue",
    "Komsomolskaya Street",
    "Chekhov Lane",
    "Mayakovsky Street",
    "Naberezhnaya River",
    "Moscow Highway",
    "Freedom Street",
    "Zelenograd Boulevard",
    "Petrovskaya Street",
    "Bolshevik Avenue",
    "Troitskaya Street",
    "Yaroslavl Road",
    "Kremlin Way",
    "Dzerzhinsky Street",
    "Baumanskaya Street",
    "Nevsky Prospect",
    "Lermontov Street",
    "Sretensky Boulevard",
    "Knyazev Street",
    "Mira Avenue",
    "Arbat Street",
    "Sakharov Avenue",
    "Shcherbakov Street",
    "Chkalov Street",
    "Kirov Street",
    "Zhukov Avenue",
    "Leningrad Avenue",
    "Vavilov Street",
    "Griboedov Canal Street",
    "Andreevsky Lane",
    "Pavlovskaya Street",
    "Smolenskaya Street"
]

def generate_data(size):
    directory = "data"
    filename = f"database_{size}.txt"
    if not os.path.exists(directory):
        os.makedirs(directory)
    filepath = os.path.join(directory, filename)

    with open(filepath, "w", encoding="utf-8") as file:
        for _ in range(size):
            print(_)
            order = f"{russian_surnames[random.randint(0, len(russian_surnames) - 1)]}"
            order += f";{russian_names[random.randint(0, len(russian_names) - 1)]}"
            order += (
                f";IU{random.randint(1, 9)}-{random.randint(1, 8)}{random.randint(0, 9)}B"
            )
            order += f";{gender[random.randint(0, 1)]}"
            order += f";{round(random.randint(6,25) / random.randint(3, 5), 2)}"

            mode = modes[random.randint(0, 2)]
            order += f";{mode}"

            if mode == "H":
                order += f";{random.randint(1, 20)}"
                order += f";{random.randint(1, 65534)}"
            else:
                order += f";{russian_street_names[random.randint(0, len(russian_street_names) - 1)]}"
                order += f";{random.randint(1, 300)}"
                order += f";{random.randint(1, 1000)}"
                if (mode == 'R'):
                    order += f";{random.randint(1, 100000)}"

            order += "\n"
            file.write(order)


if __name__ == "__main__":
    i = 4
    while i < 1000:
        generate_data(i)
        i *= 2
    generate_data(999)
