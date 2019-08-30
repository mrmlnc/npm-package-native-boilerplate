#include <nan.h>

#include "sum.cc"
#include "async.cc"
#include "sync.cc"

NAN_MODULE_INIT(init)
{
	Nan::Export(target, "sum", SumAsyncMethod::sum);
	Nan::Export(target, "sumSync", SumSyncMethod::sum);
}

NODE_MODULE(sum, init);
