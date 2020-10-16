echo "First build both cpp and Swift binaries."
echo "Then run this in the root directory of ListArrayComparison."
echo "Removing output files..."
rm *.tsv
echo "Running cpp tests..."
cpp/ninja/ListArrayComparison 1000 5 cpp-data.tsv
echo "Running Swift tests..."
swift/build/Release/SwiftListArrayComparison 1000 5 swift-data.tsv
echo "-- Tests done -- "
