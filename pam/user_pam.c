/**
 * An example program that shows how to use PAM to authenticate a user.
 *
 * See: https://github.com/linux-pam/linux-pam/blob/master/examples/check_user.c
 *
 * pam_start(3)
 * pam_authenticate(3)
 * pam_acct_mgmt(3)
 * pam_end(3)
 *
 * Compile with `-lpam -lpam_misc`
 */

#include <security/pam_appl.h>
#include <security/pam_misc.h>
#include <stdbool.h>
#include <stdio.h>

static struct pam_conv conv = {
    misc_conv,      /* Use the default conversation function from pam_misc */
    NULL
};

static bool authenticate(void);

/**
 * Use PAM to authenticate a user.
 */
int main(int argc, const char **argv)
{
    puts("Start");
    if (authenticate()) {
        puts("User authenticated");
    } else {
        puts("Authentication failed!");
        return 2;
    }

    /* The program does something useful here. */
    for (int i = 0; i < argc; i++) {
        printf("--- argv[%d] = '%s'\n", i, argv[i]);
    }

    puts("Done");
    return 0;
}

/**
 * Use PAM to authenticate the user.
 * It uses the authentication and account management operations defined in
 * `/etc/pam.d/user_pam`.  The default is `pam_unix.so` which prompts for
 * a username and password.
 * @retval true Auth Success
 * @retval false Auth Failure (or any error)
 */
static bool authenticate(void)
{
    const char *service_name = "user_pam";
    pam_handle_t *pam_handle = NULL;
    int pam_result = 0;

    /* Open PAM */
    pam_result = pam_start(service_name, NULL, &conv, &pam_handle);
    if (pam_result != PAM_SUCCESS) {
        fprintf(stderr, "Failed to initialize PAM: %s\n",
                pam_strerror(pam_handle, pam_result));
        pam_end(pam_handle, pam_result);
        return false;
    }

    /* Auth user */
    pam_result = pam_authenticate(pam_handle, 0);
    if (pam_result != PAM_SUCCESS) {
        fprintf(stderr, "Authentication failed: %s\n",
                pam_strerror(pam_handle, pam_result));
        pam_end(pam_handle, pam_result);
        return false;
    }

    /* Check user's account */
    pam_result = pam_acct_mgmt(pam_handle, 0);
    if (pam_result != PAM_SUCCESS) {
        fprintf(stderr, "Account management failed: %s\n",
                pam_strerror(pam_handle, pam_result));
        pam_end(pam_handle, pam_result);
        return false;
    }

    /* Get the user's account name */
    char *username = "";
    pam_get_item(pam_handle, PAM_USER, (const void **)&username);
    fprintf(stderr, "User '%s'\n", username);

    //pam_chauthtok();
    //pam_open_session();
    //pam_close_session();

    /* Close PAM */
    pam_end(pam_handle, pam_result);
    return true;
}

