#!/bin/sh

########################################################################
# This script is used to check the progress of Framework build on Mac. #
# A file which names FRAME_CI_Build_Finished will be touched in a      #
# shared folder, which is defined by $WORKSPACE.  The script will exit #
# the while-loop once the flag file is detected.                       #
########################################################################
#Set variables
WORKSPACE=$FRAMEWORK_CI_SHARED_FOLDER
BUILD_JOB_FINISHED_FLAG="Framework_CI_Build_Finished"

# Wait until build job is finished
echo "Waiting until build job is finished"
echo "Waiting..."
while [ 1 ]
do
    if [ -f $WORKSPACE/$BUILD_JOB_FINISHED_FLAG ]; then
        break
    else
        sleep 5
    fi
done
