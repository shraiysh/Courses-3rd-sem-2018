class APPLICATION
create make
feature
	men_pref: ARRAY2[INTEGER]
	women_pref: ARRAY2[INTEGER]
	N: INTEGER
	valid_pref: BOOLEAN

feature
	make
		local
			i, j, man, woman: INTEGER
		do
			io.read_integer
			N := io.last_integer
			print("N=" + N.out + "%N")
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

			print("%N MEN %N")
			display(men_pref)
			print("%N WOMEN %N")
			display(women_pref)
			get_stable_marriage
		end

	is_valid_pref
		require
			men_pref /= Void
			women_pref /= Void
		local
			N: INTEGER
		do
			if men_pref.height = women_pref.width and men_pref.width = women_pref.height
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

	get_stable_marriage
		require
			men_pref /= Void
			women_pref /= Void
			men_pref.height = men_pref.width and women_pref.width = women_pref.width and men_pref.height = women_pref.height
			N = men_pref.height
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
				print("%N")
				from w := 1
				until w > N or is_free.item(w) = false
				loop w := w + 1
				end
				-- Found the first free woman index in w
				print("Next free woman:" + w.out + "%N")
				from i := 1
				until i > N or is_free.item(w) = true
				loop
					m := women_pref.item (w,i)
					print("her_preference: " + m.out + "%N")
					if partner.item (m) = -1 then
						print("he is free too. map " + m.out + " to " + w.out + "%N")
						partner.put (w, m)
						is_free.put (true, w)
						free := free - 1
					else
						-- m is not free
						w1 := partner.item (m)
						print("he is not free. He prefers " + w1.out + "%N")
						if m_pref_earlier(m, w, w1) = w then
							print(w.out + " is preffered earlier => changing " + m.out + " -> " + w.out + "%N")
							partner.put (w, m)
							is_free.put (true, w)
							is_free.put (false, w1)
							print(w1.out + "is free again%N")
						end			-- end inner if
					end				-- end outer if
					i := i+1
				end					-- end inner loop
			end						-- end outer loop
			-- Print our proposal
			print("MAN%TWOMAN%N")
			from i := 1
			until i > N
			loop
				print(i.out + "%T" + partner.item (i).out + "%N")
				i := i + 1
			end
		end							-- end feature
end
