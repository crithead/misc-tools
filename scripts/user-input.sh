#!/bin/bash
#
# RETURN VALUE
# Returns 0 if the script exits normally, i.e. the user chooses not to
# continue. Returns 2 if the user chooses to quit.

# ASK what to do
function ask
{
	while true; do
		echo -n "$1 (Y/N/Q) "
		read -r ans
		case $ans in
		[Yy]*) return 0 ;;
		[Nn]*) return 1 ;;
		[Qq]*) exit 2 ;;
		*)
			echo "huh?"
			continue
			;;
		esac
	done
}

while true; do
	if ask "Continue?" ; then
		echo "Okay, keeping on"
	else
		echo "Stopping"
		break
	fi
done

echo "Done"

exit 0

