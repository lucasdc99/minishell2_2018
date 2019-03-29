/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2018
** File description:
** get_commands
*/

#include "my.h"

int count_commands(char *str)
{
    int counter = 1;
    int neighbor = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '|') {
            if (check_error_pipe(str, i) == 84)
                return (84);
            counter++;
            neighbor++;
        }
        else {
            if (neighbor == 3)
                return (84);
            else
                neighbor = 0;
        }
    }
    return (counter);
}

int get_length_one_cmd(char *str)
{
    int length = 0;

    for (int i = 0; str[i] != '|' && str[i] != '\0'; i++)
        length++;
    return (length);
}

char **get_tab_command(struct data data, char *str)
{
    int a = 0;
    int b = 0;
    data.command[a] = malloc(sizeof(char) * get_length_one_cmd(str));

    for (int i = 0; str[i] != '\0' && str[i + 1] != '>' &&
    str[i + 1] != '<'; i++) {
        if (str[i + 1] == '|') {
            data.command[a][b] = '\0';
            a++;
            i += 2;
            b = 0;
            data.command[a] = malloc(sizeof(char) * get_length_one_cmd(str));
        } else {
            data.command[a][b] = str[i];
            b++;
        }
    }
    data.command[a][b] = '\0';
    data.command[a + 1] = NULL;
    return (data.command);
}

static int check_next_command(char *str, int nbr)
{
    for (int i = nbr; str[i] != '\0'; i++) {
        if (str[i] != ' ' && str[i] != ';')
            return (nbr + 1);
    }
    return (84);
}

char *get_actual_command_line(char *str)
{
    char *actual;
    static int i = 0;
    int a = 0;

    if (str == NULL || str[i] == '\0' || i == 84) {
        i = 0;
        return (NULL);
    } else
        actual = malloc(sizeof(char) * my_strlen(str));
    for (; str[i] != '\0' && str[i] != ';'; i++) {
        actual[a] = str[i];
        a++;
    }
    if (str[i] != '\0')
        i = check_next_command(str, i);
    actual[a] = '\0';
    return (actual);
}