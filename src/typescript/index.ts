// eslint-disable-next-line @typescript-eslint/no-require-imports
import bindings = require('bindings');

type Callback = (error: NodeJS.ErrnoException | null, result: number) => void;

export type AddonApi = {
	sum(a: number, b: number, callback: Callback): void;
	sumSync(a: number, b: number): number;
};

const { sum, sumSync } = bindings('addon.node') as AddonApi;

export {
	sum,
	sumSync
};
