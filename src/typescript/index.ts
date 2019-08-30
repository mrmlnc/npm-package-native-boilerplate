import bindings = require('bindings');

type Callback = (error: NodeJS.ErrnoException, result: number) => void;

export interface AddonApi {
	sum(a: number, b: number, callback: Callback): void;
	sumSync(a: number, b: number): number;
}

const { sum, sumSync } = bindings('addon.node') as AddonApi;

export {
	sum,
	sumSync
};
