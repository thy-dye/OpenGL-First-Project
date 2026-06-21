#pragma HALFEDGE

class HalfEdge {
public:
  HalfEdge();  
  ~HalfEdge();

  HalfEdge(const HalfEdge& halfedge);  
  HalfEdge& operator=(const HalfEdge& halfedge);  

  HalfEdge(HalfEdge&& halfedge);
  HalfEdge& operator=(HalfEdge&& halfedge);  
private:

};