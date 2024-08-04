# Linux System Service

An example template for a Linux daemon.

## Installation

```sh
install -m 0644 daemon-template.service /usr/systemd/system/templated.service
systemctl daemon-reload
systemctl enable templated.service
systemctl start templated.service
systemctl status -l templated.service
```

## References

- systemd(8)
- https://systemd.io

