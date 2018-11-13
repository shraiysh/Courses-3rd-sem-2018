class APPLICATION
create make
feature
	men_pref: ARRAY2[INTEGER]
	women_pref: ARRAY2[INTEGER]
	marriage: ARRAY[INTEGER]
	N: INTEGER
	valid_pref: BOOLEAN

feature
	make
		local
			i, j, man, woman: INTEGER
		do
			io.read_integer
			N := io.last_integer
			create men_pref.make_filled (-1, N, N)
			from i:=1
			until i > N
			loop
				io.read_real
				man := io.last_real.truncated_to_integer
				from j:=1
				until j > N
				loop
					io.read_real
					men_pref.put (io.last_real.truncated_to_integer, man, j)
					j := j+1
				end
				i := i+1
			end
			create women_pref.make_filled (-1, N, N)
			from i:=1
			until i > N
			loop
				io.read_real
				woman := io.last_real.truncated_to_integer
				from j:=1
				until j > N
				loop
					io.read_real
					women_pref.put (io.last_real.truncated_to_integer, woman, j)
					j := j+1
				end
				i := i+1
			end
			set_is_valid_pref

			marriage := get_stable_marriage		-- marriage[i] stores partner of i-th man
			-- Print our proposal
			across 1 |..| N as t loop
				print(marriage.item(t.item).out + "%N")
			end
		end

	set_is_valid_pref
	-- Sets the value of class variable valid_pref by chacking the preferences: All men must be rank all women and vice versa
		require
			nothing: true
		local
			temp: ARRAY[BOOLEAN]
		do
			valid_pref := men_pref /= Void
							and women_pref /= Void
							and men_pref.height = men_pref.width and women_pref.width = women_pref.width and men_pref.height = women_pref.height
							and N = men_pref.height
			across 1 |..| N as ic loop
				create temp.make_filled (false, 1, N)
				across 1 |..| N as jc loop
					temp.put (true, men_pref.item (ic.item, jc.item))
				end
				valid_pref := valid_pref and across 1 |..| N as jc all
					temp.item (jc.item)
				end
				temp.fill_with (false)
				across 1 |..| N as jc loop
					temp.put (true, women_pref.item (ic.item, jc.item))
				end
				valid_pref:=valid_pref and across 1 |..| N as jc all
					temp.item (jc.item)
				end
			end
		end

	display(display_matrix: ARRAY2[INTEGER])
		require
			nothing: true
		local
			i,j: INTEGER
		do
			from i := 1
			invariant
				i <= display_matrix.height + 1
			until i > display_matrix.height
			loop
				from j := 1
				invariant
					j <= display_matrix.width + 1
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

	m_pref_earlier(m, w, w1: INTEGER): INTEGER
	require
		is_valid: valid_pref
		valid_index_men: m <= men_pref.height
		valid_index_women: w <= men_pref.width and w1 <= men_pref.width
	local
		i: INTEGER
	do
		Result := 0
		from i := 1
		until i > N or men_pref.item (m, i) = w1 or men_pref.item (m, i) = w
		loop i := i + 1
		end
		if i /= N+1 then
			Result := men_pref.item (m, i)
		end
		ensure


	end

	get_stable_marriage: ARRAY[INTEGER]
		require
			not_void: men_pref /= Void and women_pref /= Void
			compatiable_dimensions : men_pref.height = men_pref.width and women_pref.width = women_pref.width and men_pref.height = women_pref.height
			currect_N: N = men_pref.height
			valid_pref: valid_pref
		local
			partner: ARRAY[INTEGER]
			is_free: ARRAY[BOOLEAN]
			free, m, w, i, w1: INTEGER
		do
			create partner.make_filled (-1, 1, N)	-- Indexed by men
			create is_free.make_filled (false, 1, N)	-- Indexed by women

			from free := N
			until free <= 0
			loop
				from w := 1
				invariant
					w >= 1 and w <= N + 1
				until w > N or is_free.item(w) = false
				loop w := w + 1
				end
				-- Found the first free woman index in w

				from i := 1
				until i > N or is_free.item(w) = true
				loop
					m := women_pref.item (w,i)
					-- Found her prefernece in m and if he is not married, marry them!
					if partner.item (m) = -1 then
						partner.put (w, m)
						is_free.put (true, w)
						free := free - 1
					else
						-- m is not free
						w1 := partner.item (m)
						if m_pref_earlier(m, w, w1) = w then
							partner.put (w, m)
							is_free.put (true, w)
							is_free.put (false, w1)
						end			-- end inner if
					end				-- end outer if
					i := i+1
				end					-- end inner loop
			end						-- end outer loop
			Result := partner
			ensure
				is_valid_marriage: 
				across 1 |..| N as ic all
					across 1 |..| N as jc some
						Result.item (ic.item) = jc.item
					end
				end
		end							-- end feature
end
