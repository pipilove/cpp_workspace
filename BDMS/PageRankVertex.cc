/**
* @KCore-graph .cc
* author:pika
* This file implements the KCore-graph algorithm using graphlite API.
*
*/
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "GraphLite.h"

#define VERTEX_CLASS_NAME(name) KCoreVertex##name
#define EPS 1e-6
#define VERTEX_TYPE int64_t
#define EDGE_TYPE double
#define MSG_TYPE int64_t
int64_t k;

class VERTEX_CLASS_NAME(InputFormatter): public InputFormatter {
public:
	int64_t getVertexNum() {
		unsigned long long n;
		sscanf(m_ptotal_vertex_line, "%lld", &n);
		m_total_vertex= n;
		return m_total_vertex;
	}
	int64_t getEdgeNum() {
		unsigned long long n;
		sscanf(m_ptotal_edge_line, "%lld", &n);
		m_total_edge= n;
		return m_total_edge;
	}
	int getVertexValueSize() {
		m_n_value_size = sizeof(VERTEX_TYPE);
		return m_n_value_size;
	}
	int getEdgeValueSize() {
		m_e_value_size = sizeof(EDGE_TYPE);
		return m_e_value_size;
	}
	int getMessageValueSize() {
		m_m_value_size = sizeof(MSG_TYPE);
		return m_m_value_size;
	}
	void loadGraph() {
		unsigned long long last_vertex;
		unsigned long long from;
		unsigned long long to;
		double weight = 0;

		double value = 1;
		int outdegree = 0;

		const char *line= getEdgeLine();

		// Note: modify this if an edge weight is to be read
		//       modify the 'weight' variable

		sscanf(line, "%lld %lld", &from, &to);
		addEdge(from, to, &weight);

		last_vertex = from;
		++outdegree;
		for (int64_t i = 1; i < m_total_edge; ++i) {
			line= getEdgeLine();

			// Note: modify this if an edge weight is to be read
			//       modify the 'weight' variable

			sscanf(line, "%lld %lld", &from, &to);
			if (last_vertex != from) {
				addVertex(last_vertex, &value, outdegree);
				last_vertex = from;
				outdegree = 1;
			} else {
				++outdegree;
			}
			addEdge(from, to, &weight);
		}
		addVertex(last_vertex, &value, outdegree);
	}
};

class VERTEX_CLASS_NAME(OutputFormatter): public OutputFormatter {
public:
	void writeResult() {
		int64_t vid;
		VERTEX_TYPE value;
		char s[1024];

		for (ResultIterator r_iter; ! r_iter.done(); r_iter.next() ) {
			r_iter.getIdValue(vid, &value);
			if(value >=k){
				int n = sprintf(s, "%lld\n", (unsigned long long)vid);
				writeNextResLine(s, n);
			}
		}
	}
};

// An aggregator that records a double value tom compute sum
class VERTEX_CLASS_NAME(Aggregator): public Aggregator<double> {
public:
	void init() {
		m_global = 0;
		m_local = 0;
	}
	void* getGlobal() {
		return &m_global;
	}
	void setGlobal(const void* p) {
		m_global = * (double *)p;
	}
	void* getLocal() {
		return &m_local;
	}
	void merge(const void* p) {
		m_global += * (double *)p;
	}
	void accumulate(const void* p) {
		m_local += * (double *)p;
	}
};

class VERTEX_CLASS_NAME(): public Vertex <VERTEX_TYPE, EDGE_TYPE, MSG_TYPE> {
public:
	void compute(MessageIterator* pmsgs) {
		VERTEX_TYPE val = getValue();
		if (getSuperstep() == 0) {
			val = getOutEdgeIterator().size();  //init degree
		} else {
			if (getSuperstep() >= 2) {
				double global_val = * (double *)getAggrGlobal(0);
				if (global_val < EPS) {
					voteToHalt(); return;
				}
			}

			if(getValue() >= k){
				MSG_TYPE sum = 0;
				for ( ; ! pmsgs->done(); pmsgs->next() ) {
					sum += pmsgs->getValue();
				}
				val = sum;
			}

			double acc = fabs(getValue() - val);
			accumulateAggr(0, &acc);
		}

		* mutableValue() = val;
		if(getValue() >=k)
			sendMessageToAllNeighbors(1);
	}
};

class VERTEX_CLASS_NAME(Graph): public Graph {
public:
	VERTEX_CLASS_NAME(Aggregator)* aggregator;

public:
	// argv[0]: PageRankVertex.so
	// argv[1]: <input path>
	// argv[2]: <output path>
	// argv[3]: <k value of kcore>
	void init(int argc, char* argv[]) {

		setNumHosts(5);
		setHost(0, "localhost", 1411);
		setHost(1, "localhost", 1421);
		setHost(2, "localhost", 1431);
		setHost(3, "localhost", 1441);
		setHost(4, "localhost", 1451);

		if (argc < 4) {
			printf ("Usage: %s <input path> <output path> <k value of kcore>\n", argv[0]);
			exit(1);
		}

		m_pin_path = argv[1];
		m_pout_path = argv[2];
		k=atoi(argv[3]);    //set k of kcore

		aggregator = new VERTEX_CLASS_NAME(Aggregator)[1];
		regNumAggr(1);
		regAggr(0, &aggregator[0]);
	}

	void term() {
		delete[] aggregator;
	}
};

/* STOP: do not change the code below. */
extern "C" Graph* create_graph() {
	Graph* pgraph = new VERTEX_CLASS_NAME(Graph);

	pgraph->m_pin_formatter = new VERTEX_CLASS_NAME(InputFormatter);
	pgraph->m_pout_formatter = new VERTEX_CLASS_NAME(OutputFormatter);
	pgraph->m_pver_base = new VERTEX_CLASS_NAME();

	return pgraph;
}

extern "C" void destroy_graph(Graph* pobject) {
	delete ( VERTEX_CLASS_NAME()* )(pobject->m_pver_base);
	delete ( VERTEX_CLASS_NAME(OutputFormatter)* )(pobject->m_pout_formatter);
	delete ( VERTEX_CLASS_NAME(InputFormatter)* )(pobject->m_pin_formatter);
	delete ( VERTEX_CLASS_NAME(Graph)* )pobject;
}
