rm sources.mk
echo "SRC		:= " | tr -d '\n' >> sources.mk
find src -name *.c | sed -e s/$/' \\'/  >> sources.mk
echo "" >> sources.mk
echo "HDR		:= " | tr -d '\n' >> sources.mk
find src -name *.h | sed -e s/$/' \\'/ >> sources.mk