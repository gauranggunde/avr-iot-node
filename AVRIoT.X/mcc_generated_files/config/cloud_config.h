#ifndef CLOUD_CONFIG_H
#define CLOUD_CONFIG_H

#ifdef AWS_IOT
//Thing ID configuration

//Use this thing ID in the event of not reading it from WINC
#define AWS_THING_ID        ""  

#elif GOOGLE_IOT
// <h> Cloud Configuration

// <s> project id
// <i> Google Cloud Platform project id
// <id> project_id
#define CFG_PROJECT_ID "avr-iot"


// <s> project region
// <i> Google Cloud Platform project region
// <id> project_region
#define CFG_PROJECT_REGION "us-central1"

// <s> registry id
// <i> Google Cloud Platform registry id
// <id> registry_id
#define CFG_REGISTRY_ID "AVR-IOT"

// </h>

#endif
#endif // CLOUD_CONFIG_H
