enum MxStatus      mbox_check_stats(struct Mailbox *m, CheckStatsFlags flags);
enum MxStatus      mbox_check      (struct Mailbox *m);
enum MxStatus      mbox_close      (struct Mailbox *m);
bool               mbox_open_append(struct Mailbox *m, OpenMailboxFlags flags);
enum MxOpenReturns mbox_open       (struct Mailbox *m);
enum MxStatus      mbox_sync       (struct Mailbox *m);
