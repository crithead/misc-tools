# Linux System Service

An example template for a SysV-style Linux daemon.
See daemon(7) for more about how to write a daemon.

## Installation

```sh
install -m 0644 daemon-template.service /usr/systemd/system/templated.service
systemctl daemon-reload
systemctl enable templated.service
systemctl start templated.service
systemctl status -l templated.service
```

## References

- daemon(7)
- systemd(8)
- https://systemd.io

