#include <stdio.h>
#include "Circuit.h"

static Circuit xANDyORNOTx() {
	char *title = "X AND Y OR NOT X";

	int NINPUTS = 2;
	Boolean x = new_Boolean(false);
	Boolean y = new_Boolean(false);
	Boolean *inputs = new_Boolean_array(NINPUTS);
	inputs[0] = x;
	inputs[1] = y;

	int NOUTPUTS = 1;
	Boolean res = new_Boolean(false);
	Boolean *outputs = new_Boolean_array(NOUTPUTS);
	outputs[0] = res;

	int NGATES = 3;
	Gate and = new_AndGate();
	Gate or = new_OrGate();
	Gate not = new_Inverter();
	Gate *gates = new_Gate_array(NGATES);
	gates[0] = and;
	gates[1] = or;
	gates[2] = not;

	Circuit circuit = new_Circuit(title, NINPUTS, inputs, NOUTPUTS, outputs, NGATES, gates);

	Circuit_connect(circuit, x, Gate_getInput(and, 0));
	Circuit_connect(circuit, y, Gate_getInput(and, 1));
	Boolean xANDy = Gate_getOutput(and);

	Circuit_connect(circuit, x, Gate_getInput(not, 0));
	Boolean notx = Gate_getOutput(not);

	Circuit_connect(circuit, xANDy, Gate_getInput(or, 0));
	Circuit_connect(circuit, notx, Gate_getInput(or, 1));
	Boolean xANDyORNOTx = Gate_getOutput(or);

	Circuit_connect(circuit, xANDyORNOTx, res);

	return circuit;
}

static Circuit nor3Circuit() {
	char *title = "(X NOR Y) NOR (X NOR Y)";

	int NINPUTS = 2;
	Boolean x = new_Boolean(false);
	Boolean y = new_Boolean(false);
	Boolean *inputs = new_Boolean_array(NINPUTS);
	inputs[0] = x;
	inputs[1] = y;

	int NOUTPUTS = 1;
	Boolean res = new_Boolean(false);
	Boolean *outputs = new_Boolean_array(NOUTPUTS);
	outputs[0] = res;

	int NGATES = 3;
	Gate NOR1 = new_NorGate();
	Gate NOR2 = new_NorGate();
	Gate NOR3 = new_NorGate();
	Gate *gates = new_Gate_array(NGATES);
	gates[0] = NOR1;
	gates[1] = NOR2;
	gates[2] = NOR3;

	Circuit circuit = new_Circuit(title, NINPUTS, inputs, NOUTPUTS, outputs, NGATES, gates);

	Circuit_connect(circuit, x, Gate_getInput(NOR1, 0));
	Circuit_connect(circuit, y, Gate_getInput(NOR1, 1));
	Boolean xNORy1 = Gate_getOutput(NOR1);

	Circuit_connect(circuit, x, Gate_getInput(NOR2, 0));
	Circuit_connect(circuit, y, Gate_getInput(NOR2, 1));
	Boolean xNORy2 = Gate_getOutput(NOR2);

	Circuit_connect(circuit, xNORy1, Gate_getInput(NOR3, 0));
	Circuit_connect(circuit, xNORy2, Gate_getInput(NOR3, 1));
	Boolean final = Gate_getOutput(NOR3);

	Circuit_connect(circuit, final, res);

	return circuit;
}

static Circuit orNot3Circuit() {
	char *title = "((X OR NOT Y) AND (Y OR NOT Z)) AND (Z OR NOT X)";

	int NINPUTS = 3;
	Boolean x = new_Boolean(false);
	Boolean y = new_Boolean(false);
	Boolean z = new_Boolean(false);
	Boolean* inputs = new_Boolean_array(NINPUTS);
	inputs[0] = x;
	inputs[1] = y;
	inputs[2] = z;

	int NOUTPUTS = 1;
	Boolean res = new_Boolean(false);
	Boolean* outputs = new_Boolean_array(NOUTPUTS);
	outputs[0] = res;

	int NGATES = 8;
	Gate or1 = new_OrGate();
	Gate not1 = new_Inverter();
	Gate and1 = new_AndGate();
	Gate or2 = new_OrGate();
	Gate not2 = new_Inverter();
	Gate and2 = new_AndGate();
	Gate or3 = new_OrGate();
	Gate not3 = new_Inverter();
	Gate *gates = new_Gate_array(NGATES);
	gates[0] = or1;
	gates[1] = not1;
	gates[2] = and1;
	gates[3] = or2;
	gates[4] = not2;
	gates[5] = and2;
	gates[6] = or3;
	gates[7] = not3;

	Circuit circuit = new_Circuit(title, NINPUTS, inputs, NOUTPUTS, outputs, NGATES, gates);

	Circuit_connect(circuit, y, Gate_getInput(not1, 0));
	Boolean noty = Gate_getOutput(not1);

	Circuit_connect(circuit, z, Gate_getInput(not2, 0));
	Boolean notz = Gate_getOutput(not2);

	Circuit_connect(circuit, x, Gate_getInput(not3, 0));
	Boolean notx = Gate_getOutput(not3);

	Circuit_connect(circuit, x, Gate_getInput(or1, 0));
	Circuit_connect(circuit, noty, Gate_getInput(or1, 1));
	Boolean xORNOTy = Gate_getOutput(or1);

	Circuit_connect(circuit, y, Gate_getInput(or2, 0));
	Circuit_connect(circuit, notz, Gate_getInput(or2, 1));
	Boolean yORNOTz = Gate_getOutput(or2);

	Circuit_connect(circuit, z, Gate_getInput(or3, 0));
	Circuit_connect(circuit, notx, Gate_getInput(or3, 1));
	Boolean zORNOTx = Gate_getOutput(or3);

	Circuit_connect(circuit, xORNOTy, Gate_getInput(and1, 0));
	Circuit_connect(circuit, yORNOTz, Gate_getInput(and1, 1));
	Boolean xORNOTyANDyORNOTz = Gate_getOutput(and1);

	Circuit_connect(circuit, zORNOTx, Gate_getInput(and2, 0));
	Circuit_connect(circuit, xORNOTyANDyORNOTz, Gate_getInput(and2, 1));
	Boolean final = Gate_getOutput(and2);

	Circuit_connect(circuit, final, res);

	return circuit;
}

static void testCircuit(Circuit circuit, int ninputs, int noutputs) {
	printf("\nTruth Table:\n");

	for (int j = ninputs - 1; j >= 0; j--) {
		printf("%c ", 'x' + (ninputs - 1 - j));
	}
	printf("-> output\n");

	for (int i = 0; i < 1 << ninputs; i++) {

		for (int j = ninputs - 1; j >= 0; j--) {
			Circuit_setInput(circuit, j, i >> j & 1);
		}

		Circuit_update(circuit);

		for (int j = ninputs - 1; j >= 0; j--) {
			printf("%d ", i >> j & 1);
		}

		printf("-> ");
		for (int j = 0; j < noutputs; j++) {
			printf("%s ", Boolean_toString(Circuit_getOutput(circuit, j)));
		}
		printf("\n");
	}
}

int main(int argc, char **argv) {
	Circuit circuitA = xANDyORNOTx();
	Circuit_dump(circuitA);
	printf("\n");
	testCircuit(circuitA, Circuit_numInputs(circuitA), Circuit_numOutputs(circuitA));
	free_Circuit(circuitA);
	printf("\n");

	Circuit circuitB = nor3Circuit();
	Circuit_dump(circuitB);
	printf("\n");
	testCircuit(circuitB, Circuit_numInputs(circuitB), Circuit_numOutputs(circuitB));
	free_Circuit(circuitB);
	printf("\n");

	Circuit circuitC = orNot3Circuit();
	Circuit_dump(circuitC);
	printf("\n");
	testCircuit(circuitC, Circuit_numInputs(circuitC), Circuit_numOutputs(circuitC));
	free_Circuit(circuitC);
	printf("\n");

	return 0;
}