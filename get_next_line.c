/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabahmad <sabahmad@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/23 13:45:25 by sabahmad          #+#    #+#             */
/*   Updated: 2026/10/24 14:34:06 by sabahmad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char *readstash(int fd, char *stash)
{
  char *buffer;
  char *temp;
  ssize_t bytes;

  buffer = malloc((size_t)BUFFER_SIZE + 1);
  if (!buffer)
    return (free(stash), NULL);
  bytes = 1;
  while (!ft_strchr(stash, '\n') && bytes > 0)
  {
    bytes = read(fd, buffer, BUFFER_SIZE);
    if (bytes < 0)
      return (free(buffer), free(stash), NULL);
    buffer[bytes] = '\0';
    if (bytes == 0)
      break;
    temp = ft_strjoin(stash, buffer);
    free(stash);
    stash = temp;
    if (!stash)
      return (free(buffer), NULL);
  }
  free(buffer);
  return (stash);
}

static char *extract(char *stash)
{
  size_t len;

  len = 0;
  while (stash[len] && stash[len] != '\n')
    len++;
  if (stash[len] == '\n')
    len++;
  return (ft_substr(stash, 0, len));
}

static char *modify(char *stash)
{
  size_t i;
  char *rest;

  i = 0;
  while (stash[i] && stash[i] != '\n')
    i++;
  if (!stash[i])
    return (free(stash), NULL);
  rest = ft_strdup(stash + i + 1);
  free(stash);
  if (!rest || !rest[0])
    return (free(rest), NULL);
  return (rest);
}

char *get_next_line(int fd)
{
  static char *stash;
  char *line;

  if (fd < 0 || BUFFER_SIZE <= 0)
    return (free(stash), stash = NULL, NULL);
  if (!stash)
    stash = ft_strdup("");
  if (!stash)
    return (NULL);
  stash = readstash(fd, stash);
  if (!stash || !stash[0])
    return (free(stash), stash = NULL, NULL);
  line = extract(stash);
  if (!line)
    return (free(stash), stash = NULL, NULL);
  stash = modify(stash);
  return (line);
}
