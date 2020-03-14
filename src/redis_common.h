/*  
 * pmacct (Promiscuous mode IP Accounting package)
 *
 * Copyright (c) 2003-2020 Paolo Lucente <paolo@pmacct.net>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

/* defines */
#define PM_REDIS_DEFAULT_PORT		6379
#define PM_REDIS_DEFAULT_TIMEOUT	60
#define PM_REDIS_DEFAULT_EXP_TIME	60
#define PM_REDIS_DEFAULT_CONN_RETRY	(PM_REDIS_DEFAULT_EXP_TIME / 5)

/* structures */
struct p_redis_host {
  char log_id[SHORTBUFLEN];
  int exp_time;
  int async;
  time_t last_conn;

  redisContext *ctx;
  redisAsyncContext *actx;
  redisReply *reply;
};

/* prototypes */
extern void p_redis_init(struct p_redis_host *, char *, int);
extern int p_redis_connect(struct p_redis_host *, int);
extern void p_redis_process_reply(struct p_redis_host *);
extern void p_redis_close(struct p_redis_host *);

extern void p_redis_async_process_reply(redisAsyncContext *, void *, void *);
extern void p_redis_async_connect_cb(const redisAsyncContext *, int);
extern void p_redis_async_disconnect_cb(const redisAsyncContext *, int);

extern void p_redis_set_log_id(struct p_redis_host *, char *);
extern void p_redis_set_exp_time(struct p_redis_host *, int);
extern void p_redis_set_async(struct p_redis_host *, int);

extern void p_redis_set_string(struct p_redis_host *, char *, char *, int);
extern void p_redis_set_int(struct p_redis_host *, char *, int, int);
extern void p_redis_ping(struct p_redis_host *);

/* global vars */
extern struct p_redis_host nfacctd_redis_host;
