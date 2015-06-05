cat << CTAG
{
    name:I/O,
    elements:[
    { STitleBar:{
		title:"Internal Storage Settings"
	}},
	{ SOptionList:{
		title:"I/O Scheduler",
		default:sio,
		action:"bracket-option /sys/block/mmcblk0/queue/scheduler",
		values:[
`
			for IOSCHED in \`cat /sys/block/mmcblk0/queue/scheduler | sed -e 's/\]//;s/\[//'\`; do
			  echo "\"$IOSCHED\","
			done
`
		]
	}},
	{ SSeekBar:{
		title:"I/O read-ahead buffer",
		max:4096, min:128, unit:" kB", step:128,
		default:128,
                action:"generic /sys/devices/virtual/bdi/179:0/read_ahead_kb",
	}},
{ SPane:{
		title:"External Storage Settings"
	}},	
	{ SOptionList:{
		title:"I/O Scheduler",
		default:sio,
		action:"bracket-option /sys/block/mmcblk1/queue/scheduler",
		values:[
`
			for IOSCHED in \`cat /sys/block/mmcblk1/queue/scheduler | sed -e 's/\]//;s/\[//'\`; do
			  echo "\"$IOSCHED\","
			done
`
		]
	}},
	{ SSeekBar:{
		title:"I/O read-ahead buffer",
		max:4096, min:128, unit:" kB", step:128,
		default:128,
                action:"generic /sys/block/mmcblk1/queue/read_ahead_kb",
	}},
   ]
}

CTAG
