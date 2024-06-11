/*
 * SPDX-License-Identifier: GPL-2.0
 *
 * Simple utility which I use to generate TCP port numbers from
 * easy-to-remember strings.
 */

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Program name */
static char *prog_name;

static inline void
set_prog_name (const char *argv0)
{
  prog_name = strrchr(argv0, '/');
  if (!prog_name)
    prog_name = (char *) argv0;
  else
    ++prog_name;
}

static inline void
usage_short (void)
{
  fprintf(stderr, "Usage: %s <args...>\n", prog_name);
  exit(1);
}

static inline void
verror (const char *format, va_list args)
{
  fprintf(stderr, "%s: Error: ", prog_name);
  vfprintf(stderr, format, args);
  fputc('\n', stderr);
}

static inline void
error (const char *format, ...)
{
  va_list args;

  va_start(args, format);
  verror(format, args);
  va_end(args);
}

static inline void
die (const char *format, ...)
{
  va_list args;

  va_start(args, format);
  verror(format, args);
  va_end(args);

  exit(EXIT_FAILURE);
}

#ifndef DEBUG_BUILD
# define DEBUG(message, ...)
#else
# define DEBUG(message, ...)                               \
do                                                         \
{                                                          \
  fprintf(stderr, "DEBUG: " message "\n", ## __VA_ARGS__); \
} while (0)
#endif

int
main (int argc, char **argv)
{
  long opt_add = -1;
  long opt_mult = -1;
  int opts_end = 0;

  set_prog_name(argv[0]);

  if (argc < 2)
    usage_short();

  for (int i = 1; i < argc; i++, opts_end++)
  {
    const char *arg = argv[i];
    char *strtol_endptr = NULL;

    if (arg[0] != '-')
    {
      DEBUG("breaking out of option-parsing loop");
      break;
    }

    if (strncmp(arg, "--sum", 5) == 0)  // strlen("--sum") == 5
    {
      const char *p = arg + 6;

      if (!p)
      {
        opts_end++;
        continue;
      }

      die("Invalid option '%s'", arg);
    }

    if (strncmp(arg, "--add=", 6) == 0)  // strlen("--add=") == 6
    {
      const char *p = arg + 6;

      if (!p)
        die("Option --add requires an integer argument");

      opt_add = strtol(p, &strtol_endptr, 10);
      if (*strtol_endptr)
        die("Argument '%s' to --add is not a valid integer", p);
      else if (opt_add < 1)
        die("Argument '%s' to --add must be a positive integer", p);

      DEBUG("Parsed --add option argument opt_add = %ld", opt_add);

      opts_end++;
      continue;
    }

    if (strncmp(arg, "--mult=", 7) == 0) // strlen("--mult=") == 7
    {
      const char *p = arg + 7;

      if (!p)
        die("Option --mult requires an integer argument");

      opt_mult = strtol(p, &strtol_endptr, 10);
      if (*strtol_endptr)
        die("Argument '%s' to --mult is not a valid integer", p);
      else if (opt_mult < 1)
        die("Argument '%s' to --mult must be a positive integer", p);

      DEBUG("Parsed --mult option argument opt_mult = %ld", opt_mult);

      opts_end++;
      continue;
    }

    die("Unexpected argument '%s'", arg);
  }

  DEBUG("argc = %d", argc);
  DEBUG("opts_end = %d", opts_end);
  DEBUG("argv[opts_end] = %s", argv[opts_end - 1]);

  if (opts_end == argc)
  {
    long tot = 0;
    const char *arg = argv[opts_end - 1];
    int arg_len = strlen(arg);
    long sum;

    printf("argv[] = %s\n\n", arg);

    for (int j = 0; j < arg_len; j++)
    {
      const char ch = arg[j];
      printf("%c = %d\n", ch, ch);
      tot += ch;
    }

    sum = tot + opt_add;
    printf("\nASCII SUM: %ld\n", tot);

    if (opt_add > 0)
      printf("ADD: %ld + %ld = %ld\n", tot, opt_add, sum);
    if (opt_mult > 0)
      printf("MULT: %ld * %ld = %ld\n", opt_mult, sum, opt_mult * sum);
  }

  return EXIT_SUCCESS;
}

/*
 * vim: ts=2 sw=2 et fdm=marker :
 */
