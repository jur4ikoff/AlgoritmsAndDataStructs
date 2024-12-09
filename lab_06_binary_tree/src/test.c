#include "test.h"
#include "menu.h"
#include <stdio.h>
#include <string.h>
#include "binary_tree.h"
#include "constants.h"

void test_binaty_tree(void)
{
    // Инициализация переменных
    printf("Подпрограмма для тестирования бинарного дерева\n");
    int test_itteration_count = 0;
    test_menu_t test_operation = TEST_COUNT;
    tree_t *tree = NULL;
    // create_tree(&tree);

    // Запуск главного цикла
    while (test_operation != TEST_EXIT)
    {
        // Раз в 3 иттерации выводим меню
        if (test_itteration_count % 4 == 0)
        {
            test_menu();
        }
        test_itteration_count++;

        // Ввод операции
        printf(">>Введите тестовую операцию: ");
        test_operation = input_test_operation();
        if (test_operation == TEST_EXIT)
        {
            printf("%sУспешный выход из режима тестирования\n%s", GREEN, RESET);
            goto exit;
        }
        else if (test_operation == TEST_ADD)
        {
            ;
        }
        else if (test_operation == TEST_UNKNOWN)
        {
            printf("%sНеизвестная операция\n%s", YELLOW, RESET);
        }
    }

exit:
    tree_free(tree);
}
