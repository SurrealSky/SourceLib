#include"demo.h"
#include"../CommonLib/LogLib/log4z.h"
using namespace zsummer::log4z;

/* pseudo random number generator with 128 bit internal state... probably not suited for cryptographical usage */
typedef struct
{
	uint32_t a;
	uint32_t b;
	uint32_t c;
	uint32_t d;
} prng_t;

static prng_t prng_ctx;

static uint32_t prng_rotate(uint32_t x, uint32_t k)
{
	return (x << k) | (x >> (32 - k));
}

static uint32_t prng_next(void)
{
	uint32_t e = prng_ctx.a - prng_rotate(prng_ctx.b, 27);
	prng_ctx.a = prng_ctx.b ^ prng_rotate(prng_ctx.c, 17);
	prng_ctx.b = prng_ctx.c + prng_ctx.d;
	prng_ctx.c = prng_ctx.d + e;
	prng_ctx.d = e + prng_ctx.a;
	return prng_ctx.d;
}

static void prng_init(uint32_t seed)
{
	uint32_t i;
	prng_ctx.a = 0xf1ea5eed;
	prng_ctx.b = prng_ctx.c = prng_ctx.d = seed;

	for (i = 0; i < 31; ++i)
	{
		(void)prng_next();
	}
}





static void ecdh_demo(void)
{
	static uint8_t puba[ECC_PUB_KEY_SIZE];
	static uint8_t prva[ECC_PRV_KEY_SIZE];
	static uint8_t seca[ECC_PUB_KEY_SIZE];
	static uint8_t pubb[ECC_PUB_KEY_SIZE];
	static uint8_t prvb[ECC_PRV_KEY_SIZE];
	static uint8_t secb[ECC_PUB_KEY_SIZE];
	uint32_t i;

	/* 0. Initialize and seed random number generator */
	static int initialized = 0;
	if (!initialized)
	{
		prng_init((0xbad ^ 0xc0ffee ^ 42) | 0xcafebabe | 666);
		initialized = 1;
	}

	/* 1. Alice picks a (secret) random natural number 'a', calculates P = a * g and sends P to Bob. */
	for (i = 0; i < ECC_PRV_KEY_SIZE; ++i)
	{
		prva[i] = prng_next();
	}
	assert(ecdh_generate_keys(puba, prva));

	/* 2. Bob picks a (secret) random natural number 'b', calculates Q = b * g and sends Q to Alice. */
	for (i = 0; i < ECC_PRV_KEY_SIZE; ++i)
	{
		prvb[i] = prng_next();
	}
	assert(ecdh_generate_keys(pubb, prvb));

	/* 3. Alice calculates S = a * Q = a * (b * g). */
	assert(ecdh_shared_secret(prva, pubb, seca));

	/* 4. Bob calculates T = b * P = b * (a * g). */
	assert(ecdh_shared_secret(prvb, puba, secb));

	/* 5. Assert equality, i.e. check that both parties calculated the same value. */
	for (i = 0; i < ECC_PUB_KEY_SIZE; ++i)
	{
		assert(seca[i] == secb[i]);
	}
}

int main()
{
	ILog4zManager::getRef().setLoggerPath(LOG4Z_MAIN_LOGGER_ID, "./log");
	ILog4zManager::getRef().start();
	ILog4zManager::getRef().setLoggerLevel(LOG4Z_MAIN_LOGGER_ID, LOG_LEVEL_TRACE);

	LOGD("start");
	LOGD("tag" << ":" << "start to log");
	char buffer[] = { 0x12,0x13 };
	LOGD("hex data" << ":" << Log4zBinary(buffer, sizeof(buffer)));


	ecdh_demo();

	SurrealMemMgr::MemMgr &memmgr= SurrealMemMgr::MemMgr::GetInstance();
	memmgr.SetDebug2File(true);
	STu8 *p1=memmgr.CommonAlloc(SurrealMemMgr::TypeSGIAllocTAlloc, 100);
	STu8 *p2 = memmgr.CommonAlloc(SurrealMemMgr::TypeSGIHeapAllocTAlloc, 200);
	STu8 *p3 = memmgr.CommonAlloc(SurrealMemMgr::TypeSGIMTAllocatorAlloc, 200);
	STu8 *p4 = memmgr.CommonAlloc(SurrealMemMgr::TypeSGIVirtualAllocTAlloc, 200);

	CHttpMaker maker;
	maker.add_param("1", "2");
	return 0;
}