class APPLICATION
create make

feature
	matrix, inverse: ARRAY2[DOUBLE]
	N: INTEGER
	epsilon: DOUBLE

feature
	make
		local
			i, j: INTEGER
		do
			epsilon:= 1.0e-6
			io.read_integer
			N:=io.last_integer
			create matrix.make_filled (0, N, N)
			from i := 1
			invariant
				i<=N+1
			until i > N
			loop
				from j := 1
				invariant
					j <= N+1
				until j > N
				loop
					io.read_real
					matrix.put (io.last_real, i, j)
					j:=j+1
				end
				i:=i+1
			end

			if get_inverse then
				display(inverse)
			else
				print("INVALID%N")
			end	-- endif
		end		-- make ends

	get_inverse: BOOLEAN
		require
			matrix.height = matrix.width	-- Assumed square matrix
		local
			M: ARRAY2[DOUBLE]
			i, j, k, l: INTEGER
			first_non_zero: INTEGER
			pivot_value, value, factor: DOUBLE
		do
			N := matrix.height
			Result := true	-- Assumed inverse exists!
			create inverse.make_filled (0, N, N)
			-- Copy original matrix in first N cols and identity in next N cols
			M := get_augumented_matrix(matrix)

			from
				i := 1
				j := 1
			until j > N and i > N
			loop
				first_non_zero := get_first_non_zero_index(M, i, j)	-- At or After row i in col j
				if first_non_zero = -1 then
					Result := false
				else
					if first_non_zero /= i then
						swap(M, i, first_non_zero)
					end

					pivot_value := M.item (i, j)
					-- Divide i-th row by pivot_value to make M[i,j] equal to 1
					from k := 1
					until k > 2 * N
					loop
						M.put (M.item (i, k)/pivot_value, i, k)
						k := k + 1
					end

					-- Change others in the col to zero

					from k := 1
					until k > N
					loop
						if k /= i then
							factor := M.item (k, j) / M.item (i, j)
							row_operation(M, k, i, (-1)*factor)
							-- Scale the row M[k,l] = M[k,l] - (M[k,j] / M[i,j]) * M[i,l]
						end
						k := k + 1
					end
				end
				j := j + 1
				i := i + 1
			end
			-- Extract inverse
			set_inverse_as_second_half(M)
			ensure
				correct_inverse:
				Result implies isIdentity(matrix_multiplication(matrix, inverse))
		end

	row_operation(M: ARRAY2[DOUBLE]; a, b: INTEGER; factor: DOUBLE)
	-- Change R(a) = R(a) + factor * R(b)
		require
			valid_dim: 1 <= a and a <= M.height and 1 <= b and b <= M.height
			distinct_params: a/=b

		local
			l: INTEGER
			value: DOUBLE
		do
			from l := 1
			until l > 2 * N
			loop
				value := M.item (a, l) + factor * M.item (b, l)
				M.put (value, a, l)
				l := l + 1
			end
			ensure
				-- All except a-th row are same
				across 1 |..| M.height as row all
					across 1 |..| M.width as col all
						row /= a implies
						M.item (row.item, col.item) = (old M).item (row.item, col.item)
					end
				end
		end

	set_inverse_as_second_half(M: ARRAY2[DOUBLE])
		require
			-- M is the augumented matrix
			epsilon_not_void: epsilon /= Void

			valid_augumented_matrix_dim_after_computation : M.width = M.height * 2

			first_half_identity:
			across 1 |..| M.height as row all
				across 1 |..| M.height as col all
					(row.item = col.item implies (
						M.item (row.item, col.item) < 1 + epsilon and
						M.item (row.item, col.item) > 1 - epsilon
					))
					and
					(row.item /= col.item implies (
						M.item (row.item, col.item) < 0 + epsilon and
						M.item (row.item, col.item) > 0 - epsilon
					))
				end
			end

		local
			i, j: INTEGER
		do
			from i := 1
			until i > M.height
			loop
				from j := M.width // 2 + 1
				until j > M.width
				loop
					inverse.put (M.item (i, j), i, j-M.width//2)
					j := j + 1
				end
				i := i + 1
			end
		end

	get_augumented_matrix(P: ARRAY2[DOUBLE]): ARRAY2[DOUBLE]
		require
			P.height = P.width
		local
			Q: ARRAY2[DOUBLE]
			i, j: INTEGER
		do
			create Q.make_filled (0, P.height, 2*P.width)
			from i := 1
			until i > N
			loop
				from j := 1
				until j > 2 * N
				loop
					if j <= N then
						Q.put (matrix.item (i, j), i, j)
					elseif i + matrix.width = j then
						Q.put (1, i, j)
					else
						Q.put (0, i, j)
					end
					j := j + 1
				end
				i := i + 1
			end
			Result := Q

			ensure
				valid_dim : Result.height * 2 = Result.width

				first_half_same_and_second_half_identity:
				across 1 |..| Result.height as row all
					-- First half
					across 1 |..| Result.height as col all
						Result.item (row.item, col.item) = matrix.item (row.item, col.item)
					end

					and
					-- Second Half is identity
					across (Result.height + 1) |..| Result.width as col all

						row.item = (col.item - Result.height) implies
						Result.item (row.item, col.item) = 1

						and row.item /= (col.item - Result.height) implies
						Result.item (row.item, col.item) = 0

					end
				end
		end

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
					print(display_matrix.item (i,j).out +" ")
					j := j + 1
				end
				print("%N")
				i := i + 1
			end
		ensure
			nothing: true
		end

	get_first_non_zero_index (M: ARRAY2[DOUBLE]; i, j: INTEGER): INTEGER
	-- Gives y-index of first non zero entry after(including) i-th row
	-- If all are zeroes, it gives -1
		require
			1 <= i and i <= M.height and 1 <= j and j <= M.width
		local
			k : INTEGER
		do
			from k := i
			until k > N or M.item (k, j) /= 0
			loop k := k + 1
			end

			if k = N + 1 then
				-- All are zeroes
				Result := -1
			else
				Result := k
			end
			ensure
				Result_holds_first_non_zero :
				Result /= -1 implies (
				1 <= Result and Result <= M.height and M.item(i, Result) /= 0 and
					across i |..| (Result - 1) as row all
						M.item (row.item, j) > 0-epsilon and M.item (row.item, j) < 0+epsilon
					end
				)
		end

	swap(M: ARRAY2[DOUBLE]; i, j: INTEGER)
		require
			valid_dim : 1 <= i and i <= M.height and 1 <= j and j <= M.width
			distinct_args : i /= j
		local
			temp: ARRAY[DOUBLE]
			k: INTEGER
		do
			create temp.make_filled (0, 1, M.width)
			from k := 1
			until k > M.width
			loop
				temp.item (k) := M.item (i, k)
				k := k + 1
			end
			from k := 1
			until k > M.width
			loop
				M.item (i, k) := M.item (j, k)
				k := k + 1
			end
			from k := 1
			until k > M.width
			loop
				M.item (j, k) := temp.item (k)
				k := k + 1
			end
			ensure
				rest_matrix_same_as_earlier:
				across 1 |..| M.height as row all
					across 1 |..| M.width as col all
						((row.item /= i and row.item /= j) implies
						M.item (row.item, col.item) = (old M).item (row.item, col.item))
					end
				end

				i_and_j_swapped:
				across 1 |..| M.width as col all
					M.item(i, col.item) = (old M).item(j, col.item)
					and
					M.item(j, col.item) = (old M).item(i, col.item)
				end
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

		isIdentity(M: ARRAY2[DOUBLE]): BOOLEAN
	-- Checks if a matrix is Identity matrix or not.(Input can be a rectangular matrix too)
		require
			epsilon /= Void
		local
			i, j:INTEGER
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
						if i=j and (M.item (i, j) < 1 - epsilon or M.item (i, j) > 1 + epsilon) then
							-- check along diagonal
							Result := Result and false
						elseif i/=j and (M.item (i, j) < 0 - epsilon or M.item (i, j) > 0 + epsilon) then
							-- check for non-diagonal
							Result := Result and false
						end		-- end if
						j:=j+1
					end			-- end j loop
					i:=i+1
				end				-- end i loop
			end					-- end if
		end					-- end feature
end
