#!/bin/bash
sudo cp `dirname $0`/libmediaplayerplugin.so /usr/lib/dde-dock/plugins/system-trays/libmediaplayerplugin.so
killall dde-dock
dde-dock