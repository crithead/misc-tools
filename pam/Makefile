# Build a PAM module

CFLAGS += -Wall -Werror -std=c11 -O2

ifeq ($(V),1)
E =
else
E = @
endif

all: pam_notice.so pam_notice.8.gz user_pam

pam_notice.so: pam_notice.o
	$(E)$(LD) -x --shared -o $@ $^

pam_notice.o: pam_notice.c
	$(E)$(CC) $(CFLAGS) -fPIC -fno-stack-protector -c $^

pam_notice.8.gz: pam_notice.8
	$(E)gzip -k $^

user_pam: user_pam.c
	$(E)$(CC) $(CFLAGS) -o $@ $^ -lpam -lpam_misc

.PHONY: install
install: pam_notice.so pam_notice.8.gz etc-pam.d-user_pam
	$(E)install -u root -g root -m 0755 pam_notice.so /usr/lib64/security
	$(E)install -u root -g root -m 0644 pam_notice.8.gz /usr/share/man/man8
	$(E)install -u root -g root -m 0644 -T etc-pam.d-user_pam /etc/pam.d/user_pam

.PHONY: uninstall
uninstall:
	$(E)rm -f /usr/lib64/security/pam_notice.so
	$(E)rm -f /usr/share/man/man8/pam_notice.8.gz
	$(E)rm -f /etc/pam.d/user_pam

.PHONY: clean
clean:
	$(E)rm -f pam_notice.so pam_notice.o pam_notice.8.gz user_pam

