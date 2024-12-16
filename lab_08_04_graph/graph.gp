digraph G {
    0 -> 1 [label="5"];
    0 -> 2 [label="8"];
    0 -> 3 [label="6"];
    0 -> 4 [label="7"];
    1 -> 0 [label="5"];
    1 -> 2 [label="9"];
    1 -> 4 [label="4"];
    2 -> 0 [label="8"];
    2 -> 1 [label="9"];
    2 -> 3 [label="2"];
    3 -> 0 [label="6"];
    3 -> 2 [label="2"];
    3 -> 4 [label="5"];
    4 -> 0 [label="7"];
    4 -> 1 [label="4"];
    4 -> 3 [label="5"];
    0 [style=filled, fillcolor=green];
    1 [style=filled, fillcolor=red];
    2 [style=filled, fillcolor=green];
    3 [style=filled, fillcolor=white];
    4 [style=filled, fillcolor=green];
}
