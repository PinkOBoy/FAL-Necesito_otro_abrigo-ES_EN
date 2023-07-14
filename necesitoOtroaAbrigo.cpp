/*
* @author PinkOBoy
*/
/* RESUMEN DEL ENUNCIADO // SUMING UP THE INSTRUCTIONS
* 
* // - SPANISH -------------------------------------------------------------
* Tenemos a una persona que quiere vestir durante dias de lluvia distintos
* abrigos con distintas resistencias a la lluvia. Esa seleccion tiene que
* seguir ciertas normas:
* 
*	- El abrigo que se ponga un dia ha que tener mayor resistencia que la
*		cantidad de lluvia que va caer ese dia.
*	- No puede vestir el mismo abrigo por dias consecutivos.
*	- El numero de veces que vista un abrigo no puede ser mayor que un
*		tercio de la cantidad de dias que han pasado.
*	- El abrigo usado el primer dia no puede coincidir con el usado el
*		ultimo dia.
* 
* Esta persona dice que es imposible hacer esa seleccion. Nosotros tenemos
* que escribir un código que sea capaz de mostrar las distintas soluciones
* que se pueden dar con los datos de entrada, asi como el numero de
* soluciones obtenidas.
* 
* 
* //- ENGLISH --------------------------------------------------------------
* There's a person who wants to wear, on certain rainy days, differents coats
* with differents rain resistance. This selection of coats has to follow
* certain rules:
* 
*	- The coat that's wore on a day must have more resistance than the amount of
*		rain which's going to fall that day.
*	- They cannot wear the same coat for consecutive days.
*	- The times they has wore a coat cannot be greater than a third of the
*		number of days which have already passed.
*	- The coat used the first day cannot coincide with the one used the last
*		day.
* 
* This person says it's impossible to make that selection. We have to code a
* solution that's able to show the different possible options we can get with
* the input parameters, and also the number of differents obtained solutions.
*/
/*
* Problema de vuelta atras que NO es del tipo de la mochila.
* 
* Backtracking problem which is NOT of the backpack type.
*/

#include <iostream>
#include <vector>
using namespace std;

// - PROTOTIPOS ----------------------------------------------------------------------
// - PROTOTYPES

// Funcion de combinacion // combination function
void resolver(
	const vector<int>& dias,	// vector de dias con la cantidad de lluvias	// vector of days with their amount of rain
	const vector<int>& abrigos,	// vector de abrigos con las resistencias		// vector of coats with their rain resistance
	vector<int>& sol,			// solucion con los abrigos usados cada dia		// solution with the coats used each day
	vector<int>& marcas,		// # dias que se ha utilizado cada abrigo		// # days each coat was used
	int& numSol,				// # soluciones obtenidas						// # obtained solutions
	int dia						// dia actual analizado							// current analyzed day
);

// Funcion de verificacion // Partial Solution Check function
bool esValida(
	int dia,
	int abrigo,
	const vector<int>& dias,
	const vector<int>& abrigos,
	const vector<int>& sol,
	const vector<int>& marcas
);

// - MAIN ----------------------------------------------------------------------------

bool solve() {
	// read solution
	int nDias;
	cin >> nDias;
	if (nDias <= 0)
		return false;

	int nAbrigos;
	cin >> nAbrigos;

	vector<int> d(nDias), 
		sol(nDias),
		a(nAbrigos),
		marcas(nAbrigos, 0);

	for (int i = 0; i < d.size(); ++i)
		cin >> d[i];
	for (int i = 0; i < a.size(); ++i)
		cin >> a[i];

	// compute solution

	int numSol = 0;
	resolver(d, a, sol, marcas, numSol, 0);

	// write solution
	cout << numSol << endl;

	return true;
}

int main() {
	while (solve());
	return 0;
}

// - IMPLEMENTACIONES ----------------------------------------------------------------
// - IMPLEMENTATIONS

/* COMPLEJIDAD DEL ALGORITMO:
* En este algoritmo, recorremos TODAS las variaciones con repeticion entre
* los distintos dias y los distintos abrigos. Esto se debe a la arquitectura
* de realizar llamadas recursivas, cada cual equivalente al día concreto al
* que le estamos asignando un abrigo, y al bucle for del código, que hace que
* en cada llamada recorramos los distintos abrigos para poner uno en la solucion.
*
* Todas las instrucciones ejecutadas son de coste constante.
*
* Con esto en mente, definimos:
*
*	n::= sol.size() = dias.size()
*
*	r::= abrigos.size()
*
* Y declaramos que el coste de eficiencia del algoritmo será:
*
*	O(n ^  r)
*/

/* COMPLEXITY OF THE ALGORITHM:
* This algorithm ranges all the variations with repetitions between days and coats.
* This is granted thanks to the way of making the recursive calls, each equivalent
* to a day when we choose a coat; and thanks to the for loop, which ranges all coats
* in each call of us to put a value in the solution vector.
* 
* All executed instructions have a constant complexity.
* 
* Considering all that, we define:
*	
*	n::= sol.size() = days.size()
* 
*	r::= coats.size()
* 
* So we can affirm the efficiency cost of the algorithm will be:
* 
*	O(n ^ r)
*/
void resolver(
	const vector<int>& dias,	
	const vector<int>& abrigos,	
	vector<int>& sol,
	vector<int>& marcas,
	int& numSol,
	int dia
) {
	// Recorremos los abrigos
	// Ranging the coats
	for (int i = 0; i < abrigos.size(); ++i) {

		// Probamos el abrigo i
		// We try using the i coat 
		sol[dia] = i;

		// Marcamos el abrigo i como ya usado
		// We mark that coat as used
		++marcas[i];

		// Si con este abrigo, la solicion parcial sigue siendo valida
		// If by using that coat, the partial solution is still valid
		if (esValida(dia, i, dias, abrigos, sol, marcas)) {

			// Si ya hemos terminado de construir una solucion completa
			// If by using that coat, we have completed the solution
			if (dia == dias.size() - 1) {
				/*
				* No todas las restricciones se pueden comprobar en
				* esValida(), puesto que dicha funcion esta generalizada
				* para cualquier etapa, y a veces queremos evaluar
				* condiciones en etapas concretas.
				* 
				* La ultima restriccion impuesta por el problema es:
				*
				*	El abrigo usado el primer dia no puede coincidir con
				*	el abrigo usado el ultimo dia.
				* 
				* Por ello, aqui comprobamos dicha condicion antes de
				* dar por finalizada la busqueda de esta solucion.
				* 
				* Tecnicamente, si se podria meter esa condicion en 
				* esValida(), pero eso la complicaria.
				*/
				/*
				* Not all restrictions/conditions can be checked out in
				* isValid(), because this function should be evaluating
				* general conditions to be satisfied in every single
				* stage, and sometimes we need to verify conditions for
				* particular stages.
				* 
				* The last restriction imposed by the problem's instructions is:
				* 
				*	- The coat used the first day cannot coincide with the one
				*     used the last	day.
				* 
				* Thus, here we check out if that condition before finishing
				* the search of this solution.
				* 
				* Technically, it is possible to check out that condition
				* in isValid(), but by doing that, you would make it more complex.
				*/

				if (sol[0] != sol[dia]) {

					// Sol es solucion, entonces aumentamos el contador de soluciones
					// Sol IS a solution, so we increase the solution counter
					++numSol;

					// Mostramos la solucion por pantalla
					// We print the solution
					cout << "Solucion " << numSol << ": ";
					for (int j = 0; j < sol.size(); ++j) {
						int aux = sol[j];
						cout << abrigos[aux] << ' ';
					}						
					cout << endl << endl;
				}

			}
			// Si todavia NO hemos terminado de construir la solucion.
			// If we are not done building the solution yet.
			else
				resolver(dias, abrigos, sol, marcas, numSol, dia + 1);
		}
		// Ocurra lo que ocurra, terminamos de analizar las soluciones con el
		// abrigo i y pasaremos al siguiente
		// Whatever happens, we finished analyzing the solutions with the i coat
		// and we move on to the next one

		// Esto implica desmarcarlo.
		// That implies unmark it.
		--marcas[i];
	}
}

bool esValida(
	int dia,
	int abrigo,
	const vector<int>& dias,
	const vector<int>& abrigos,
	const vector<int>& sol,
	const vector<int>& marcas
) {
	// El abrigo tiene que tener mayor resistencia a la lluvia que la cantidad de lluvia que va a caer
	// The coat must have more rain resistance than the amount of rain that's going to fall
	if (abrigos[abrigo] < dias[dia])
		return false;
	// No puede ser el mismo abrigo que llevamos en la etapa anterior
	// It cannot be the same one that we wore the previous day
	else if (dia > 0 && sol[dia] == sol[dia - 1])
		return false;
	// No podemos llevar un abrigo mas veces que un tercio de la cantidad de dias
	// We cannot wore a coat more times than a third of the number of days
	else if (marcas[abrigo] > (dia / 3) + 2)
		return false;
	// Si cumple todo eso, es valida
	// If it satisfies all of these, it is valid.
	else return true;
}