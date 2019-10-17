The goal of this program is to take as standard input (i.e., via std::cin) a description of all of the locations on a map and the stretches of road that connect them. It then performs two tasks:

Ensures that it is possible for every location to be reached from every other location. If we think of the locations and roads as a directed graph, that boils down to the problem of determining whether the graph is strongly connected. If not, the message Disconnected Map should be output and the program should end.

Determines, for a sequence of trip requests listed in the input, shortest distances or shortest times between pairs of locations.