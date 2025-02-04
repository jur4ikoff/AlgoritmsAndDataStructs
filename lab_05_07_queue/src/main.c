/*
ЛР 5 - Очереди, Вариант 7
_______________________________________________________________________________________
Цель работы: отработка навыков работы с типом данных «очередь», представленным в виде одномерного статического массива
и односвязного линейного списка. Сравнительный анализ реализации алгоритмов включения и исключения элементов из очереди при
использовании двух указанных структур данных. Оценка эффективности
программы по времени и по используемому объему памяти.

Процент расхождения расчетного времени и получившегося при работе программы должен быть не больше 2-3%
Расчетное время моделирования (по входу) = среднее время прихода заявки* количество вошедших заявок.
Расчетное время моделирования (по выходу) = среднее время обработки заявки* количество обработанных заявок.
Если время обработки больше времени прихода, то очередь будет расти, и время моделирования будет определяться временем обработки,
а количество вошедших заявок будет = времени моделирования / среднее время прихода заявки.
Если время прихода больше времени обработки, то очереди не будет, и время моделирования будет определяться временем прихода заявок.
При написании программы обратить внимание на то, что является ВХОДНЫМИ данными для нее!

_______________________________________________________________________________________
ЗАДАНИЕ ПО ВАРИАНТУ
Система массового обслуживания состоит из обслуживающего аппарата (ОА) и очереди заявок. T1 T2
Заявки поступают в "хвост" очереди по случайному закону с интервалом времени Т1,
равномерно распределенным от 0 до 6 единиц времени (е.в.). В ОА они поступают из "головы" очереди по одной и обслуживаются также
равновероятно за время Т2 от 0 до 1 е.в., Каждая заявка после ОА вновь поступает в "хвост" очереди, совершая всего 5 циклов обслуживания,
после чего покидает систему. (Все времена – вещественного типа) В начале процесса в системе заявок нет.
Смоделировать процесс обслуживания до ухода из системы первых 1000 заявок, выдавая после обслуживания каждых 100 заявок информацию о
текущей и средней длине очереди, а в конце процесса - общее время моделирования и количестве вошедших в систему и вышедших из нее заявок,
количестве срабатываний ОА, время простоя аппарата. По требованию пользователя выдать на экран адресов элементов очереди при удалении и
добавлении элементов. Проследить, возникает ли при этом фрагментация памяти.
_______________________________________________________________________________________
*/

#include "arr_queue.h"
#include "constants.h"
#include "errors.h"
#include "list_queue.h"
#include "menu.h"
#include "simulation.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

int main(void)
{
    // Инициализация переменных
    int rc = ERR_OK;
    size_t itteration_count = 0;
    operations_t menu_operaton = OP_INIT;

    // Вывод информации о программе
    print_guide();
    while (1)
    {
        // Вывод меню раз в 3 иттерации
        if (itteration_count % 3 == 0)
            print_menu();

        // Ввод операции
        if ((rc = input_menu_operation(&menu_operaton)) != ERR_OK)
            goto exit;

        if (menu_operaton == OP_EXIT)
        {
            // Выход из программы
            printf("%sУспешный выход из программы%s\n", GREEN, RESET);
            break;
        }
        else if (menu_operaton == OP_TEST_STATIC)
        {
            // Тестирование очереди на статическом массиве
            // Запуск подпрограммы для тестирования очереди на статическом массиве
            if ((rc = arr_test()) != ERR_OK)
            {
                print_menu();
                itteration_count = 0;
            }
        }
        else if (menu_operaton == OP_TEST_LIST)
        {
            // Тестирование очереди на списке
            if ((rc = list_test()) != ERR_OK)
            {
                print_error_message(rc);
                print_menu();
                itteration_count = 0;
            }
        }
        else if (menu_operaton == OP_SIMULATION)
        {
            float list_time = 0.0, arr_time = 0.0;

            // calc_memory_usage();

            printf("\n\n");
            // Запуск симуляции для очереди на листе
            run_simulation_list_queue(&list_time);

            // Запуск симуляции для очереди на массиве
            run_simulation_arr_queue(&arr_time);
            // Вывод результатов
            printf("\n____________________\n");
            printf("Результаты симуляции\n");
            printf("Время выполнения:\n"
                   "- При использовании очереди на основе массива: %.2f мкс\n"
                   "- При использовании очереди на основе связного списка: %.2f мкс\n",
                   arr_time, list_time);
            printf("Использование очереди на основе массива эффективнее в %.2f раза\n", list_time / arr_time);
        }
        else if (menu_operaton == OP_EDIT)
        {

            // Изменение параметров
            if ((rc = edit_params()) != ERR_OK)
                goto exit;
        }
        else
        {
            printf("%sВыбрана неверная операция%s\n", YELLOW, RESET);
        }
        itteration_count++;
    }
// Метка для общего выхода из программы
exit:
    if (rc)
        print_error_message(rc);
    return rc;
}
