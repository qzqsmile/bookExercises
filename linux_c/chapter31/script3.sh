#! /bin/sh

echo "Is it moring? Plesase answer yes or no"
read YES_OR_NO
case "$YES_OR_NO" in
yes|y|Yes|YES)
	echo "Good moring!";;
[nN]*)
	echo "Good afternoon!";;
*)
	echo "Sorry, $YES_OR_NO not recognized. Enter yes or no"
	exit 1;;
esac
exit 0