#include <iostream>
#include <nan.h>

namespace SumAsyncMethod {
using v8::Function;
using v8::Local;
using v8::Number;
using v8::Value;

class SumWorker : public Nan::AsyncWorker
{
public:
	SumWorker(Nan::Callback* callback, double a, double b): Nan::AsyncWorker(callback), a(a), b(b) {}
	~SumWorker() {}

	void Execute() { int status = Sum::sum(a, b, result); }

	void HandleOKCallback()
	{
		Nan::HandleScope scope;

		Local<Value> value = Nan::New<Number>(result);
		Local<Value> argv[] = { Nan::Null(), value };

		Nan::AsyncResource resource("npm-package-native-boilerplate:addon.async");
		callback->Call(2, argv, &resource);
	}

	void HandleErrorCallback()
	{
		// Nothing
	}

private:
	double a;
	double b;
	double result;
};

NAN_METHOD(sum)
{
	if (!info[0]->IsNumber()) {
		return Nan::ThrowTypeError("the first argument must be a number");
	}
	if (!info[1]->IsNumber()) {
		return Nan::ThrowTypeError("the second argument must be a number");
	}

	if (!info[2]->IsFunction()) {
		return Nan::ThrowTypeError("'callback' argument must be a function");
	}

	double a = Nan::To<double>(info[0]).FromJust();
	double b = Nan::To<double>(info[1]).FromJust();

	Local<Function> callback = info[2].As<Function>();

	Nan::AsyncQueueWorker(new SumWorker(new Nan::Callback(callback), a, b));
}
} // namespace SumAsyncMethod
