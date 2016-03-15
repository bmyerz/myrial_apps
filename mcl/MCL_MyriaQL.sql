matA = scan(matrix); -- shbae:matrix should be replaced with actual table name.

-- define constant values as singleton tables.
epsilon = [0.001];
prunelimit = [0.00001];

-- initialize oldChaos and newChaos for stop condition.
oldchaos = [1000.0];
newchaos = [1000.0];

-- while there is an epsilon improvement
do 
	oldchaos = newchaos;

	-- square matA
	AxA = [from matA as A, matA as B
			   where A.col == B.row
			   emit A.row as row, B.col as col, sum(A.value * B.value) as value];
	
	-- inflate operation
	-- value will be value^2
	squareA = [from AxA emit row as row, col as col, value * value as value];

	colsums = [from squareA
			   emit squareA.col as col, sum(squareA.value) as colsum];
	
	-- normalize newMatA
	newMatA = [from squareA, colsums
			   where squareA.col == colsums.col
			   emit squareA.row as row, squareA.col as col, squareA.value/colsums.colsum as value];

	-- pruning
	prunedA = [from newMatA
			   where value > *prunelimit
			   emit *];

	-- calculate newchaos
	colssqs = [from prunedA
			   emit prunedA.col as col, sum (prunedA.value * prunedA.value) as sumSquare];
	colmaxs = [from prunedA
			   emit prunedA.col as col, max (prunedA.value) as maxVal];

	newchaos = [from colmaxs, colssqs
				where colmaxs.col == colssqs.col
				emit max (colmaxs.maxVal - colssqs.sumSquare)];

	-- prepare for the iteration.
	matA = prunedA;

	-- check the convergency.
	continue = [from newchaos, oldchaos emit (*oldchaos - *newchaos) > *epsilon];
while continue;

--store (newchaos, OUTPUT);
store (matA, OUTPUT);
