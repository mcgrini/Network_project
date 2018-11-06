#include "network.h"
#include "random.h"
#include <map>
#include <vector>
#include <iostream>

void Network::resize(const size_t& a) {  
						
	values.resize(a);
	RNG.normal(values);
}

bool Network::add_link(const size_t& a, const size_t& b) {
	
	if (a == b) {
		return false;
	}else if ((a > (size()-1)) or (b > (size()-1))) {
		return false;
	}else {
		
		for (auto nodes :links) {
		
			if ((nodes.first == a and nodes.second == b)){
			return false;
				}
			}
				links.insert(std::pair<size_t, size_t> (a,b));
				links.insert(std::pair<size_t,size_t> (b,a));
				return true;
	}
}
	
size_t Network::random_connect(const double& mean) {
	
	links.clear();											
	size_t successful_links(0);
	
		for (int i = 0; i < size(); ++i) {	
			int deg = RNG.poisson(mean);
			std::vector<int> nodes(deg,0);
			RNG.uniform_int(nodes,0, (size()-1));
			for (int j = 0; j < nodes.size(); ++j) {
				if (add_link(i, nodes[j])) {
					++successful_links;
				}
			}	
		}
	return successful_links;
}

size_t Network::set_values(const std::vector<double>& t) {
	
	values.clear();
	values = t;
	return size();
	
}

size_t Network::size() const {
	
	return values.size(); 
}

size_t Network::degree(const size_t &_n) const {
	return links.count(_n);
}

double Network::value(const size_t &_n) const {
		 
		return values[_n];	

}

std::vector<double> Network::sorted_values() const {
	
	std::vector<double> sortedValues(values);
	std::sort(sortedValues.begin(), sortedValues.end(), std::greater<double>()); 
	return sortedValues;
	
}

std::vector<size_t> Network::neighbors(const size_t& k) const {
	
	std::vector<size_t> liens;  			
										
		for (auto ligneMap : links) {
			if (ligneMap.first == k) {
			liens.push_back(ligneMap.second);
			}
		}
	return liens;
}

