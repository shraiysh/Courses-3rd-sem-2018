note
	description: "POPL - I Assigment 1 Matrix Inversion"
	author: "SHRAIYSH VAISHAY CS17BTECH11050"
	date: "12-11-2018"

class
	MATRIX_INVERSION

create
	make

feature
	matrix: ARRAY2[DOUBLE]
	inverse: ARRAY2[DOUBLE]
	dim: INTEGER
	allowed_error: DOUBLE	-- While checking if inverse is right, due to mechanical errors,
							-- the product of matrices can slightly deviate from identity.
							-- This variable stores the small error allowed in this inverse calculation.

feature
	make
	local
		i, j: INTEGER
	do
		allowed_error:= 1.0e-6
		io.read_integer
		dim:=io.last_integer
		create matrix.make_filled (0, dim, dim)
		from i := 1
		invariant
			i<=dim+1
		until i > dim
		loop
			from j := 1
			invariant
				j <= dim+1
			until j > dim
			loop
				io.read_real
				matrix.put (io.last_real, i, j)
				j:=j+1
			end
			i:=i+1
		end

		create inverse.make_filled (0, dim, dim)
		if get_inverse then
			display(inverse)
			else print("INVALID%N")
		end	-- endif
	end		-- make ends

	display(display_matrix: ARRAY2[DOUBLE])
		require
			nothing: true
		local
			i,j: INTEGER
		do
			from i := 1
			invariant
				i <= display_matrix.height+1
			until i > display_matrix.height
			loop
				from j := 1
				invariant
					j <= display_matrix.width+1
				until j > display_matrix.width
				loop
					print(display_matrix.item (i,j).out + " ")
					j := j + 1
				end
				print("%N")
				i := i + 1
			end
		ensure
			nothing: true
		end

	matrix_multiplication(A, B: ARRAY2[DOUBLE]): ARRAY2[DOUBLE]
	-- This returns product of A and B. Used in ensure clause for inverse and adjoint functions
		require
			A.width = B.height
		local
			C: ARRAY2[DOUBLE]		-- To store the product
			value: DOUBLE			-- To store every entry temporarily
			i, j, k: INTEGER		-- Loop variables
		do
			create C.make_filled (0, A.height, B.width)
			from i:=1
			invariant
				i <= A.height+1
			until i > A.height
			loop
				from j:=1
				invariant
					j <= B.width+1
				until j > B.width
				loop
					-- matrix multiplication A x B = C => C[i,j] = (k = 1 to n)sum(A[i,k]*B[k,j]) where dim(A) = m*n and dim(B) = n*p
					value := 0
					from k:=1
					invariant
						k <= A.width+1 and k <= B.height+1
					until k > A.width
					loop
						value := value + A.item (i, k) * b.item (k, j)
						k:=k+1
					end			-- Loop on k
					C.put (value, i, j)
					j:=j+1
				end				-- Loop on j
				i:=i+1
			end					-- Loop on i
			Result := C
			ensure
				nothing: true	-- Follows definition of matrix multiplication and hence no ensure
		end

	diagonal_matrix(d: DOUBLE; dimension: INTEGER): ARRAY2[DOUBLE]		-- Returns a diagonal matrix of size (dimension x dimension)
	-- This is used while calculating |A|.I to ensure that adj(A).A = |A|.I and hence adj(A) is correct
		require
			non_negative_dimension: dimension>=0
		local
			M: ARRAY2[DOUBLE] -- Stores the matrix locally
			i: INTEGER -- loop variable
		do
			create M.make_filled (0, dimension, dimension)
			from i:=1
			invariant
				i <= dimension+1
			until i > dimension
			loop
				m.put (d, i, i)
				i:=i+1
			end
			Result:= M
			ensure
				nothing: true
		end

	isIdentity(M: ARRAY2[DOUBLE]): BOOLEAN
	-- Checks if a matrix is Identity matrix or not.(Input can be a rectangular matrix too)
		require
			allowed_error /= Void
		local
			i, j, k:INTEGER
		do
			if M.width /= M.height then
				Result:= false
			else
				Result:= true
				from i:=1
				invariant
					i <= M.width+1
				until i > M.width
				loop
					from j:=1
					invariant
						j <= M.height+1
					until j > M.height
					loop
						if i=j and (M.item (i, j) < 1 - allowed_error or M.item (i, j) > 1 + allowed_error) then
							-- check along diagonal
							Result := Result and false
						elseif i/=j and (M.item (i, j) < 0 - allowed_error or M.item (i, j) > 0 + allowed_error) then
							-- check for non-diagonal
							Result := Result and false
						end		-- end if
						j:=j+1
					end			-- end j loop
					i:=i+1
				end				-- end i loop
			end					-- end if
		end					-- end feature

	get_inverse: BOOLEAN
	-- Stores inverse in class variable inverse and returns if the inverse exists
		local
			det, value : DOUBLE
			i, j : INTEGER
			adjoint : ARRAY2[DOUBLE]
		do
			det := get_determinant(matrix, dim)
			if det = 0 then
				Result := false
			else
				create adjoint.make_filled (1, dim, dim)
				get_adjoint(adjoint)
				from i := 1
				invariant
					i <= dim+1
				until i > dim
				loop
					from j := 1
					invariant
						i <= dim+1
					until j > dim
					loop
						value := if adjoint.item (i, j)/det = -0 then 0.0 else adjoint.item (i, j)/det end
						inverse.put (value, i, j)
						j:= j+1
					end
					i := i + 1
				end
				Result:= true
			end
			ensure
				correct_inverse: Result = true implies isIdentity(matrix_multiplication(matrix, inverse))
		end

	get_adjoint(adjoint: ARRAY2[DOUBLE])
		require
			sqaure_matrix: matrix.height = matrix.width
			same_dim_for_adj_addr: matrix.height = adjoint.height and matrix.width = adjoint.width
		local
			cofactor: ARRAY2[DOUBLE]
			sign, i, j: INTEGER
		do
			if dim = 1 then
				adjoint.put (1, 1, 1)
			else
				sign := 1
				create cofactor.make_filled (1, dim, dim)
				from i := 1
				invariant
					i <= dim+1
				until i > dim
				loop
					from j := 1
					invariant
						j <= dim+1
					until j > dim
					loop
						get_cofactor(matrix, cofactor, i, j, dim)
						sign := if (i+j)\\2 = 0 then 1 else -1 end
						adjoint.put (sign * get_determinant(cofactor, dim-1), j, i)
						j := j + 1
					end
					i := i + 1
				end
			end
			ensure
				correct_adjoint: matrix_multiplication(adjoint, matrix).same_items(diagonal_matrix(get_determinant(matrix, dim), dim))
		end

	get_determinant(myMatrix: ARRAY2[DOUBLE]; dimension: INTEGER): DOUBLE
	-- Returns det for a sub-matrix(dimension x dimension) of myMatrix
		require
			correct_dimesions: dimension <= myMatrix.height and dimension <= myMatrix.width
		local
			cofactor: ARRAY2[DOUBLE]
			sign:INTEGER
			f: INTEGER
		do
			Result := 0

			if dimension = 1 then
				Result := myMatrix.item (1, 1)
			else
				create cofactor.make_filled (1, dimension, dimension)
				sign := 1

				from f := 1
				invariant
					f <= dimension+1
				until f > dimension
				loop
					get_cofactor(myMatrix, cofactor, 1, f, dimension);
					Result := Result + sign * myMatrix.item (1, f) * get_determinant(cofactor, dimension-1)
					sign := -1 * sign
					f := f + 1
				end
			end
			ensure
				nothing: true
		end

	get_cofactor(myMatrix: ARRAY2[DOUBLE]; cofactor: ARRAY2[DOUBLE]; row, col: INTEGER; dimension: INTEGER)
		require
			correct_in_matrix_dimesion: dimension <= myMatrix.width and dimension <= myMatrix.height
			correct_out_matrix_dimension: cofactor.width >= dimension-1 and cofactor.height >= dimension-1
			correct_row: 1<=row and row<=dimension
			correct_col: 1<=col and col<=dimension
		local
			i, j, trow, tcol: INTEGER
		do
			i:=1
			j:=1
			from trow := 1
			invariant
				j <= dimension
				i <= dimension
			until trow > dimension
			loop
				from tcol := 1
				invariant
					i <= dimension
					j <= dimension
				until tcol > dimension
				loop
					if trow /= row and tcol /= col then
						cofactor.put (myMatrix.item (trow, tcol), i, j)
						j := j + 1
						if j = dimension then
							j := 1
							i := i + 1
						end
					end
					tcol := tcol+1
				end
				trow := trow + 1
			end
			ensure
				nothing: true
		end
end

