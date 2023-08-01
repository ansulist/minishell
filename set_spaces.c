/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_spaces.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansulist <ansulist@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 16:38:42 by Famahsha          #+#    #+#             */
/*   Updated: 2023/07/19 12:53:21 by ansulist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	count_pipes(char *str)
// {
// 	int		count;
// 	int		quotecount;
// 	char	*ptr;

// 	count = 0;
// 	quotecount = 0;
// 	ptr = str;
// 	while (*ptr != '\0')
// 	{
// 		if (*ptr == '\"')
// 			quotecount++;
// 		if (*ptr == '|' && (quotecount % 2 == 0))
// 		{
// 			count++;
// 			*ptr = 2;
// 		}
// 		ptr++;
// 	}
// }


int check_quotecount(char *str)
{
    int count;

    count = 0;
    while(*str)
    {
        if(check_quotes(*str) == 1)
            count++;
        str++;
    }
    if (count % 2 != 0)
    {
        ft_error();
        return (1);
    }
    else
        return (count);
}

// void   space_afterpipe(char *string)
// {
//     int length;
//     int i;

//     length = strlen(string) + 2;
//     i = 0;
//       while (i < length - 1) {
//         if (string[i] == '|' || string[i] == '<') {
//             if (string[i + 1] != ' ') {
//                 int shift_index = i;
//                 char temp = ' ';
//                 char previous_char = -1;
//                 while (shift_index < length) {
//                     char current_char = string[shift_index];
//                     string[shift_index] = temp;
//                     temp = current_char;

//                     if (previous_char == -1)
//                         previous_char = current_char;
//                     else {
//                         previous_char = temp;
//                         shift_index++;
//                     }
//                 }
//                 length++;
//                 i++;
//             }
//         }
//         i++;
//     }
// }

char *rostring(char* string)
{
    int i  = 0;
    int length = strlen(string);

    int j = 0;
    while (i < length) {
        if (string[i] != ' ' || (i > 0 && string[i - 1] != ' ')) {
            string[j] = string[i];
            j++;
        }
        i++;
    }
    string[j] = '\0';
    length = strlen(string) + 2;
    i = 0;
    while (i < length - 1) {
        if (string[i] == '|') {
            if (string[i + 1] != ' ') {
                int shift_index = i;
                char temp = ' ';
                char previous_char = -1;

                // Shift characters to the right
                while (shift_index < length) {
                    char current_char = string[shift_index];
                    string[shift_index] = temp;
                    temp = current_char;

                    if (previous_char == -1)
                        previous_char = current_char;
                    else {
                        previous_char = temp;
                        shift_index++;
                    }
                }
                length++;
                i++;
            }
        }
        i++;
    }
    return(string);
}

// char *rostring(char* string)
// {
//     int i  = 0;
//     int length = strlen(string);

//     int j = 0;
//     while (i < length) {
//         if (string[i] != ' ' || (i > 0 && string[i - 1] != ' ')) {
//             string[j] = string[i];
//             j++;
//         }
//         i++;
//     }
//     string[j] = '\0';
//     length = strlen(string) + 2;
//     i = 0;
//     while (i < length - 1) {
//         if (string[i] == '|' || string[i] == '<') {
//             if (string[i + 1] != ' ') {
//                 int shift_index = i;
//                 char temp = ' ';
//                 char previous_char = -1;

//                 // Shift characters to the right
//                 while (shift_index < length) {
//                     char current_char = string[shift_index];
//                     string[shift_index] = temp;
//                     temp = current_char;

//                     if (previous_char == -1)
//                         previous_char = current_char;
//                     else {
//                         previous_char = temp;
//                         shift_index++;
//                     }
//                 }

//                 length++;
//                 i++;
//             }
//         }
//         i++;
//     }
//     return(string);
// }

// char* rostr(char* str) 
// {
//     int quoteCount;
//     int spaceCount; 
//     int spaceReduced;

//     quoteCount = 0;
//     spaceCount = 0;
//     spaceReduced = 0;
//     char* modifiedStr = (char*)malloc((strlen(str) + 1) * sizeof(char));
//     char* modifiedPtr = modifiedStr;
//     while (*str)
//     {
//         if (check_quotes(*str) == 1)
//             quoteCount++;

//         if (*str == '|' && quoteCount % 2 == 0)
//         {
//             if (spaceCount == 0)
//             {
//                 *(modifiedPtr++) = *str;
//                 *(modifiedPtr++) = ' ';
//                 spaceCount = 1;
//                 spaceReduced = 0;
//             }
//             else
//             {
//                 while (ft_isspace(*(str + 1)))
//                     str++;
//                 spaceCount = 1;
//                 spaceReduced = 0;
//             }
//         }
//         else if (ft_isspace(*str) && spaceCount > 0 && !spaceReduced)
//         {
//             spaceCount++;
//         }
//         else
//         {
//             if (spaceCount > 1)
//             {
//                 *(modifiedPtr++) = ' ';
//                 spaceCount = 0;
//                 spaceReduced = 1;
//             }
//             else if (spaceCount == 1)
//             {
//                 *(modifiedPtr++) = ' ';
//                 spaceCount = 0;
//             }
//             *(modifiedPtr++) = *str;
//         }
//         if (check_redirection(*str) && quoteCount % 2 == 0)
//         {
//             if (ft_isspace(*(str + 1)))
//                 *(modifiedPtr++) = ' ';
//             while (ft_isspace(*(str + 1)))
//                 str++;
//         }
//         str++;
//     }
//     *modifiedPtr = '\0';
//     return modifiedStr;
// }