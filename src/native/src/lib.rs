#[macro_use]
extern crate neon;

use neon::prelude::*;

fn sum_sync(mut cx: FunctionContext) -> JsResult<JsNumber> {
	let a = cx.argument::<JsNumber>(0)?.value();
	let b = cx.argument::<JsNumber>(1)?.value();

	Ok(cx.number(a + b))
}

struct BackgroundTask {
	a: f64,
	b: f64,
}

impl Task for BackgroundTask {
	type Output = f64;
	type Error = ();
	type JsEvent = JsNumber;

	fn perform(&self) -> Result<f64, ()> {
		Ok(self.a + self.b)
	}

	fn complete(self, mut cx: TaskContext, result: Result<f64, ()>) -> JsResult<JsNumber> {
		Ok(cx.number(result.unwrap()))
	}
}

fn sum_async(mut cx: FunctionContext) -> JsResult<JsUndefined> {
	let a = cx.argument::<JsNumber>(0)?.value() as f64;
	let b = cx.argument::<JsNumber>(1)?.value() as f64;
	let cb = cx.argument::<JsFunction>(2)?;

	let task = BackgroundTask { a: a, b: b };

	task.schedule(cb);

	Ok(cx.undefined())
}

register_module!(mut cx, {
	cx.export_function("sumSync", sum_sync)?;
	cx.export_function("sum", sum_async)?;

	Ok(())
});
