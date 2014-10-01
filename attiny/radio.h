/**
 * Power Amplifier level.
 *
 * For use with setPALevel()
 */
typedef enum { RF24_PA_MIN = 0,RF24_PA_LOW, RF24_PA_HIGH, RF24_PA_MAX, RF24_PA_ERROR } rf24_pa_dbm_e ;

/**
 * Data rate.  How fast data moves through the air.
 *
 * For use with setDataRate()
 */
typedef enum { RF24_1MBPS = 0, RF24_2MBPS, RF24_250KBPS } rf24_datarate_e;

/**
 * CRC Length.  How big (if any) of a CRC is included.
 *
 * For use with setCRCLength()
 */
typedef enum { RF24_CRC_DISABLED = 0, RF24_CRC_8, RF24_CRC_16 } rf24_crclength_e;

extern uint8_t radioFlushRX(void);
extern uint8_t radioFlushTX(void);
extern void radioPrintDetails(void);
extern void radioSetChannel(uint8_t channel);
extern void radioSetPayloadSize(uint8_t size);
extern uint8_t radioGetPayloadSize(void);
extern void radioSetPALevel(rf24_pa_dbm_e level);
extern rf24_pa_dbm_e radioGetPALevel(void);
extern uint8_t radioSetDataRate(rf24_datarate_e speed);
extern rf24_datarate_e radioGetDataRate( void );
extern void radioSetCRCLength(rf24_crclength_e length);
extern rf24_crclength_e radioGetCRCLength(void);
extern void radioDisableCRC( void );
extern void radioSetRetries(uint8_t delay, uint8_t count);
extern void radioInit(void);
extern void radioStartListening(void);
extern void radioStopListening(void);
extern void radioPowerDown(void);
extern void radioPowerUp(void);
extern void radioStartWrite( const void* buf, uint8_t len );
extern void radioWhatHappened(uint8_t* tx_ok,uint8_t* tx_fail,uint8_t* rx_ready);
extern uint8_t radioWrite( const void* buf, uint8_t len );
extern uint8_t radioDataAvailable(uint8_t* pipe_num);
extern uint8_t radioRead( void* buf, uint8_t len );
extern void radioOpenWritingPipe(uint64_t value);
extern void radioOpenReadingPipe(uint8_t child, uint64_t address);
extern void radioEnableDynamicPayloads(void);
extern void radioEnableAckPayload(void);
extern void radioWriteAckPayload(uint8_t pipe, const void* buf, uint8_t len);
extern uint8_t radioIsAckPayloadAvailable(void);
extern uint8_t radioIsPVariant(void);
extern void radioSetAutoAck(uint8_t enable);
extern void radioSetAutoAck2( uint8_t pipe, uint8_t enable );
extern uint8_t radioTestCarrier(void);
extern uint8_t radioTestRPD(void);
extern volatile unsigned long getMillis(void);
