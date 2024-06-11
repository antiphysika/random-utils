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

int
main (int argc, char **argv)
{
  long opt_add = -1;
  long opt_mult = -1;
  int optind = 1;

  set_prog_name(argv[0]);

  if (argc < 2)
  {
    fprintf(stderr, "Usage: %s <args...>\n", prog_name);
    exit(1);
  }

  for (int i = 1, optind = 1; i < argc; i++, optind++)
  {
    const char *arg = argv[i];
    char *strtol_endptr = NULL;

    if (arg[0] != '-')
    {
      fprintf(stderr, "DEBUG: breaking out of option-parsing loop\n");
      break;
    }

    if (strncmp(arg, "--sum", 5) == 0)  // strlen("--sum") == 5
    {
      const char *p = arg + 6;

      if (!p)
      {
        optind++;
        continue;
      }

      fprintf(stderr, "%s: Error: Invalid option '%s'\n", prog_name, arg);
      exit(EXIT_FAILURE);
    }

    if (strncmp(arg, "--add=", 6) == 0)  // strlen("--add=") == 6
    {
      const char *p = arg + 6;

      if (!p)
      {
        fprintf(stderr, "%s: Error: Option --add requires an integer argument\n", prog_name);
        exit(EXIT_FAILURE);
      }

      opt_add = strtol(p, &strtol_endptr, 10);
      if (*strtol_endptr)
      {
        fprintf(stderr, "%s: Error: Argument '%s' to --add is not a valid integer\n", prog_name, p);
        exit(EXIT_FAILURE);
      }
      else if (opt_add < 1)
      {
        fprintf(stderr, "%s: Error: Argument '%s' to --add must be a positive integer\n", prog_name, p);
        exit(EXIT_FAILURE);
      }

      optind++;
      continue;
    }

    if (strncmp(arg, "--mult=", 7) == 0) // strlen("--mult=") == 7
    {
      const char *p = arg + 7;

      if (!p)
      {
        fprintf(stderr, "%s: Error: Option --mult requires an integer argument\n", prog_name);
        exit(EXIT_FAILURE);
      }

      opt_mult = strtol(p, &strtol_endptr, 10);
      if (*strtol_endptr)
      {
        fprintf(stderr, "%s: Error: Argument '%s' to --mult is not a valid integer\n", prog_name, p);
        exit(EXIT_FAILURE);
      }
      else if (opt_mult < 1)
      {
        fprintf(stderr, "%s: Error: Argument '%s' to --mult must be a positive integer\n", prog_name, p);
        exit(EXIT_FAILURE);
      }

      optind++;
      continue;
    }

    fprintf(stderr, "%s: Unexpected argument '%s'\n", prog_name, arg);
    exit(EXIT_FAILURE);
  }

#if 0
  fprintf(stderr, "DEBUG: optind = %d\n", optind);
  fprintf(stderr, "DEBUG: optind + 2 = %d\n", optind + 2);
  fprintf(stderr, "DEBUG: argc = %d\n", argc);
  fprintf(stderr, "DEBUG: argv[optind] = %s\n", argv[optind+2]);
#endif

  if (optind + 2 < argc)
  {
    int tot = 0;
    const char *arg = argv[optind + 2];
    int arg_len = strlen(arg);

    printf("argv[] = %s\n\n", arg);

    for (int j = 0; j < arg_len; j++)
    {
      const char ch = arg[j];
      printf("%c = %d\n", ch, ch);
      tot += ch;
    }

    printf("\nASCII SUM: %d\n", tot);

    if (opt_add > 0)
      printf("ADD: %ld + %d = %ld\n", opt_add, tot, opt_add + tot);
    if (opt_mult > 0)
      printf("MULT: %ld * (%ld + %ld) = %ld\n", opt_mult, opt_add, tot, opt_mult * (tot + opt_add));
  }

  return EXIT_SUCCESS;
}

/*
 * vim: ts=2 sw=2 et fdm=marker :
 */
