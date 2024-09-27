#include <errno.h>
#include <stdio.h>
#include <string.h>

#define FORMAT "%-16s  %4d  %s\n"
#define PRINT(X) printf(FORMAT, #X, X, strerror(X))
#define ITEM(X) { #X, X }
#define NOERR 0

struct item {
    const char *name;
    int number;
};

static const struct item ETAB[] = {
    ITEM(NOERR),
    /* asm-generic/errno-base.h */
    ITEM(EPERM),
    ITEM(ENOENT),
    ITEM(ESRCH),
    ITEM(EINTR),
    ITEM(EIO),
    ITEM(ENXIO),
    ITEM(E2BIG),
    ITEM(ENOEXEC),
    ITEM(EBADF),
    ITEM(ECHILD),
    ITEM(EAGAIN),
    ITEM(ENOMEM),
    ITEM(EACCES),
    ITEM(EFAULT),
    ITEM(ENOTBLK),
    ITEM(EBUSY),
    ITEM(EEXIST),
    ITEM(EXDEV),
    ITEM(ENODEV),
    ITEM(ENOTDIR),
    ITEM(EISDIR),
    ITEM(EINVAL),
    ITEM(ENFILE),
    ITEM(EMFILE),
    ITEM(ENOTTY),
    ITEM(ETXTBSY),
    ITEM(EFBIG),
    ITEM(ENOSPC),
    ITEM(ESPIPE),
    ITEM(EROFS),
    ITEM(EMLINK),
    ITEM(EPIPE),
    ITEM(EDOM),
    ITEM(ERANGE),
    /* asm-generic/errno.h */
    ITEM(EDEADLK),
    ITEM(ENAMETOOLONG),
    ITEM(ENOLCK),
    ITEM(ENOSYS),
    ITEM(ENOTEMPTY),
    ITEM(ELOOP),
    ITEM(EWOULDBLOCK),
    ITEM(ENOMSG),
    ITEM(EIDRM),
    ITEM(ECHRNG),
    ITEM(EL2NSYNC),
    ITEM(EL3HLT),
    ITEM(EL3RST),
    ITEM(ELNRNG),
    ITEM(EUNATCH),
    ITEM(ENOCSI),
    ITEM(EL2HLT),
    ITEM(EBADE),
    ITEM(EBADR),
    ITEM(EXFULL),
    ITEM(ENOANO),
    ITEM(EBADRQC),
    ITEM(EBADSLT),
    ITEM(EDEADLOCK),
    ITEM(EBFONT),
    ITEM(ENOSTR),
    ITEM(ENODATA),
    ITEM(ETIME),
    ITEM(ENOSR),
    ITEM(ENONET),
    ITEM(ENOPKG),
    ITEM(EREMOTE),
    ITEM(ENOLINK),
    ITEM(EADV),
    ITEM(ESRMNT),
    ITEM(ECOMM),
    ITEM(EPROTO),
    ITEM(EMULTIHOP),
    ITEM(EDOTDOT),
    ITEM(EBADMSG),
    ITEM(EOVERFLOW),
    ITEM(ENOTUNIQ),
    ITEM(EBADFD),
    ITEM(EREMCHG),
    ITEM(ELIBACC),
    ITEM(ELIBBAD),
    ITEM(ELIBSCN),
    ITEM(ELIBMAX),
    ITEM(ELIBEXEC),
    ITEM(EILSEQ),
    ITEM(ERESTART),
    ITEM(ESTRPIPE),
    ITEM(EUSERS),
    ITEM(ENOTSOCK),
    ITEM(EDESTADDRREQ),
    ITEM(EMSGSIZE),
    ITEM(EPROTOTYPE),
    ITEM(ENOPROTOOPT),
    ITEM(EPROTONOSUPPORT),
    ITEM(ESOCKTNOSUPPORT),
    ITEM(EOPNOTSUPP),
    ITEM(EPFNOSUPPORT),
    ITEM(EAFNOSUPPORT),
    ITEM(EADDRINUSE),
    ITEM(EADDRNOTAVAIL),
    ITEM(ENETDOWN),
    ITEM(ENETUNREACH),
    ITEM(ENETRESET),
    ITEM(ECONNABORTED),
    ITEM(ECONNRESET),
    ITEM(ENOBUFS),
    ITEM(EISCONN),
    ITEM(ENOTCONN),
    ITEM(ESHUTDOWN),
    ITEM(ETOOMANYREFS),
    ITEM(ETIMEDOUT),
    ITEM(ECONNREFUSED),
    ITEM(EHOSTDOWN),
    ITEM(EHOSTUNREACH),
    ITEM(EALREADY),
    ITEM(EINPROGRESS),
    ITEM(ESTALE),
    ITEM(EUCLEAN),
    ITEM(ENOTNAM),
    ITEM(ENAVAIL),
    ITEM(EISNAM),
    ITEM(EREMOTEIO),
    ITEM(EDQUOT),
    ITEM(ENOMEDIUM),
    ITEM(EMEDIUMTYPE),
    ITEM(ECANCELED),
    ITEM(ENOKEY),
    ITEM(EKEYEXPIRED),
    ITEM(EKEYREVOKED),
    ITEM(EKEYREJECTED),
    ITEM(EOWNERDEAD),
    ITEM(ENOTRECOVERABLE),
    ITEM(ERFKILL),
    ITEM(EHWPOISON),
    /* bits/errno.h */
    ITEM(ENOTSUP),
#if 0   /* duplicates */
    ITEM(ECANCELED),
    ITEM(EOWNERDEAD),
    ITEM(ENOTRECOVERABLE),
    ITEM(ERFKILL),
    ITEM(EHWPOISON),
#endif
};

#define ETAB_FIRST  1
#define ETAB_LAST  ((sizeof(ETAB) / sizeof(struct item)) - ETAB_FIRST)

static void list(void)
{
    for (int i = ETAB_FIRST; i<= ETAB_LAST; i++) {
        printf(FORMAT, ETAB[i].name, ETAB[i].number, strerror(ETAB[i].number));
    }
}

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    /* TODO Add lookup */
    /* TODO Add HTML output */
    list();
    return 0;
}
