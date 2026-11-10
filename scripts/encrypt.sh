#!/bin/bash

if [ "$#" -eq 0 ] || [ "${1}" == "-h" ] || [ "${1}" == "--help" ]; then
    cat <<EOH

    encrypt.sh -h | --help | [ -d ] file

    Encrypt or decrypt (with -d) 'file'.  Encryption adds a '.enc.xz' extension
    and decrypt removes it.  The encryption output is base64 and amenable to
    compression so it gets compressed.  The uncompressed encrypted input file is
    removed, but the original unencrypted file is left for the user to remove,
    if desired.

    -h, --help      Print usage information and exit
    -d, --decrypt   Decrypt the input file

    Return value:
        0 success
        1 encryption/decryption failed
        2 compression/decompression failed

EOH
    exit 0
fi

function scramble
{
    local input="${1}"
    local output="${input}.enc"
    if openssl enc -aes-256-cbc -pbkdf2 -a -salt -in "${input}" -out "${output}" 2> /dev/null; then
        # Leave the original file
        if xz --compress "${output}"; then
            echo "OK -- ${output}.xz"
            return 0
        else
            echo "Warning: compression failed -- ${output}"
            return 2
        fi
    else
        echo "Error: encryption failed"
        return 1
    fi
}

function descramble
{
    local input="${1}"
    if [[ ${input} =~ .xz$ ]]; then
        if xz --decompress "${input}"; then
            input=$(echo "${input}" | sed -E 's/(.*).xz$/\1/')
        else
            echo "Error: decompression failed"
            return 2
        fi
    fi
    local output=$(echo "${input}" | sed -E 's/(.*).enc$/\1/')
    if openssl enc -aes-256-cbc -pbkdf2 -a -d -in "${input}" -out "${output}" 2> /dev/null; then
        # Remove the uncompressed encrypted file
        /usr/bin/rm -f "${input}"
        echo "OK: ${output}"
        return 0
    else
        echo "Error: decryption failed"
        return 1
    fi
}

if [ "${1}" == "-d" ] || [ "${1}" == "--decrypt" ] ; then
    descramble "${2}"
    value=$?
else
    scramble "${1}"
    value=$?
fi

exit "${value}"

