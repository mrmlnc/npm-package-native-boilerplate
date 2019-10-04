import * as assert from 'assert';

import * as pkg from '.';

describe('Addon', () => {
	describe('.sum', () => {
		// Tests for non-correct arguments

		it('should return the sum of two integer numbers', (done) => {
			pkg.sum(1, 1, (error, result) => {
				if (error === null) {
					assert.strictEqual(result, 2);
				} else {
					assert.fail(error.message);
				}

				done();
			});
		});

		it('should return the sum of two float numbers', (done) => {
			pkg.sum(1.3, 1.5, (error, result) => {
				if (error === null) {
					assert.strictEqual(result, 2.8);
				} else {
					assert.fail(error.message);
				}

				done();
			});
		});
	});

	describe('.sumSync', () => {
		// Tests for non-correct arguments

		it('should return the sum of two integer numbers', () => {
			const expected = 2;

			const actual = pkg.sumSync(1, 1);

			assert.strictEqual(actual, expected);
		});

		it('should return the sum of two float numbers', () => {
			const expected = 2.8;

			const actual = pkg.sumSync(1.3, 1.5);

			assert.strictEqual(actual, expected);
		});
	});
});
