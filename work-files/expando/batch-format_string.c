    struct Buffer *buf1 = buf_pool_get();
    struct Buffer *buf2 = buf_pool_get();
    char *str = "hello-world";
    int cols;

    buf_reset(buf1);
    buf_reset(buf2);
    cols = format_string(buf1, 0, 4, JUSTIFY_RIGHT, 0, str, strlen(str), true);
    cols = format_string(buf2, 10, 10, JUSTIFY_RIGHT, ' ', buf_string(buf1), buf_len(buf1), true);
    printf("cols   = %d\n", cols);
    printf("buf1   = |%s|\n", buf_string(buf1));
    printf("result = |%s|\n", buf_string(buf2));

    buf_reset(buf1);
    buf_reset(buf2);
    cols = format_string(buf1, 4, 10, JUSTIFY_RIGHT, ' ', str, strlen(str), true);
    printf("cols   = %d\n", cols);
    printf("buf1   = |%s|\n", buf_string(buf1));
    printf("result = |%s|\n", buf_string(buf2));

    str = "🔔☠️🍓📎♥️🔔☠️🍓📎♥️🔔☠️🍓📎♥️🔔☠️🍓📎♥️";
    buf_reset(buf1);
    buf_reset(buf2);
    cols = format_string(buf1, 0, 4, JUSTIFY_RIGHT, 0, str, strlen(str), true);
    cols = format_string(buf2, 10, 10, JUSTIFY_RIGHT, ' ', buf_string(buf1), buf_len(buf1), true);
    printf("cols   = %d\n", cols);
    printf("buf1   = |%s|\n", buf_string(buf1));
    printf("result = |%s|\n", buf_string(buf2));

    buf_pool_release(&buf1);
    buf_pool_release(&buf2);
