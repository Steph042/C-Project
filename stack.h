#ifndef STACK_H
#define STACK_H

#include <ostream> // std::ostream
#include <iostream> // std::cout std::endl
#include <cassert> // assert
#include <algorithm> // std::swap

#include <cstddef>  // std::ptrdiff_t
#include <iterator> // std::forward_iterator_tag

/**
	@file stack.h
	@brief Dichiarazione della classe Stack
*/

/**
  Nodo
  @brief Dichiarazione della struct Stack
*/
template <typename T>
struct Stack{
  public:
  	typedef T value_type; ///< tipo T degli elementi contenuti nello stack
  	typedef unsigned int size_type; ///< dimensione del tipo T

  private:
    value_type* _stack; ///< array di tipo T contente lo stack
    size_type _size;  ///< dimensione dello stack

  public:
    /**
      @brief Costruttore di default

      Costruttore di default per inizializzare uno stack vuoto di dimensione 0

      @post _stack == nullptr
      @post _size = 0;
    */
    Stack() : _stack(nullptr), _size(0) {
  		#ifndef NDEBUG
  		std::cout << "Stack::Stack()" << std::endl;
  		#endif
  	}
    /**
      @brief Costruttore secondario #1

      Costruttore di secondario per inizializzare uno stack di dimensione sz
       dove ogni elemento vale value

      @param sz size_type dimensione dello stack
      @param value value_type valore passato come reference

      @post _stack inizializzato a dimensione sz e con valore value
      @post _size = sz;
    */
    Stack(size_type sz, const value_type &value) : _stack(nullptr), _size(0) {
      _stack = new value_type[sz];
      _size = sz;

      try {
        for(size_type i=0; i < _size; ++i)
          _stack[i] = value;
      }
      catch(...) {
        delete[] _stack;
        _stack = nullptr;
        _size = 0;
        throw;
      }

      #ifndef NDEBUG
      std::cout << "Stack::Stack(size_type, value_type)" << std::endl;
      #endif
    }
    /**
      @brief Costruttore di conversione

      Costruttore che coverte uno stack ad un altro tipo Q

      @param other Stack di tipo Q passato per reference

      @post _stack inizializzato a dimensione other.size() e con valori uguali a other
      @post _size = other.size()
    */
    template <typename Q>
    Stack(const Stack<Q> &other) : _stack(nullptr), _size (0) {
      _stack = new value_type[other.size()];

      try {
        for(size_type i = 0; i < other.size(); ++i)
          _stack[i] = static_cast<T>(other.value(i));
      }
      catch(...) {
        delete[] _stack;
        _stack = nullptr;
        _size = 0;
        throw;
      }
      _size = other.size();

      #ifndef NDEBUG
      std::cout << "Stack::Stack(const Stack&)" << std::endl;
      #endif
    }
    /**
  		@brief Copy constructor

      Costruttore che un nodo uguale a &other

      @param other Stack passato come reference

      @post _stack inizializzato a dimensione other.size e contente i valori di other
      @post _size = other.size()
  	*/
    Stack(const Stack &other) : _stack(nullptr), _size (0) {
      _stack = new value_type[other._size];

      try {
        for(size_type i = 0; i < other._size; ++i)
          _stack[i] = other._stack[i];
      }
      catch(...) {
        delete[] _stack;
        _stack = nullptr;
        _size = 0;
        throw;
      }
      _size = other._size;

      #ifndef NDEBUG
      std::cout << "Stack::Stack(const Stack&)" << std::endl;
      #endif
    }
    /**
      @brief Operatore di assegnamento

      Operatore di assegnamento che serve per copiare il contenuto di
      other in *this.

      @param other Stack da copiare

      @return reference a Stack
    */
    Stack& operator=(const Stack &other) {
      // auto-assegnamento a = a
      if (&other != this) { // controllo dell'auto-assegnamento
        Stack tmp(other);

        tmp.swap(*this);
      }

      #ifndef NDEBUG
      std::cout << "Stack::Stack=(const Stack&)" << std::endl;
      #endif

      return *this; // a=b=c; -> a=(b=c);
    }
    /**
      @brief Distruttore della struct

      Distruttore della struct. Rimuove dall'heap l'array dinamico _stack e
      mette _size a 0
    */
    ~Stack() {
      delete[] _stack;
      _stack = nullptr;
      _size = 0;

      #ifndef NDEBUG
      std::cout << "Stack::~Stack()" << std::endl;
      #endif
    }
    /**
      @brief Getter di _size

      Metodo const che ritorna il valore di _size

      @return _size
    */
    size_type size() const {
  		return _size;
  	}
    /**
      @brief Getter di _stack

      Metodo const che ritorna il valore dello stack all'indece index se index < _size

      @param index size_type indice del valore che viene ritornato

      @return _stack[index]
    */
    const value_type &value(size_type index) const {
      assert(index < _size);

      return _stack[index];
    }

    /**
  		@brief Funzione di swap dei dati interni tra due stack

  		Funzione che scambia gli stati interni tra due stack

  		@param other stack sorgente
  	*/
  	void swap(Stack &other) {
  		std::swap(this->_stack, other._stack);
  		std::swap(this->_size, other._size);
  	}

    /**
      @brief Metodo push

      Metodo che aggiunge l'elemento passato in cima allo stack

      @param value value_type reference al valore che deve essere aggiunto

      @post _size = _size + 1
    */
    void push(const value_type &value){
      value_type* copy_stack;

      copy_stack = new value_type[_size + 1];

      try {
        for(size_type i=0; i < _size; ++i)
          copy_stack[i] = _stack[i];

        copy_stack[_size] = value;
      }
      catch(...) {
        delete[] copy_stack;
        copy_stack = nullptr;
        throw;
      }

      delete[] _stack;
      _stack = nullptr;

      _size = _size + 1;
      _stack = new value_type[_size];

      try {
        for(size_type i=0; i < _size; ++i)
          _stack[i] = copy_stack[i];
      }
      catch(...) {
        delete[] _stack;
        _stack = nullptr;
        _size = 0;
        throw;
      }

      delete[] copy_stack;
      copy_stack = nullptr;
    }
    /**
      @brief Metodo pop

      Metodo che rimuove e ritorna l'elemento in cima allo stack

      @return res valore in cima allo stack

      @post _size = _size - 1
    */
    value_type pop(){

      if(_size == 0){
        throw "Stack is empty";
      }
      value_type res;
      value_type* copy_stack;

      copy_stack = new value_type[_size - 1];

      try {
        for(size_type i=0; i < _size - 1; ++i)
          copy_stack[i] = _stack[i];

        res = _stack[_size - 1];
      }
      catch(...) {
        delete[] copy_stack;
        copy_stack = nullptr;
        throw;
      }

      delete[] _stack;
      _stack = nullptr;

      _size = _size - 1;
      _stack = new value_type[_size];

      try {
        for(size_type i=0; i < _size; ++i)
          _stack[i] = copy_stack[i];
      }
      catch(...) {
        delete[] _stack;
        _stack = nullptr;
        _size = 0;
        throw;
      }

      delete[] copy_stack;
      copy_stack = nullptr;

      return res;
    }
    /**
      @brief Metodo clean

      Metodo che rimuove gli elementi presenti sullo stack

      @post _stack = nullptr
      @post _size = 0
    */
    void clean(){
      delete[] _stack;
      _stack = nullptr;
      _size = 0;
    }
    /**
      Iteratore
      @brief Dichiarazione della sottoclasse iterator
    */
    class iterator {
      T* ptr;

    public:
      typedef std::forward_iterator_tag iterator_category;
      typedef T                         value_type;
      typedef ptrdiff_t                 difference_type;
      typedef T*                        pointer;
      typedef T&                        reference;

      /**
        @brief Costruttore di default

        Costruttore di default per inizializzare un iterator vuoto
        @post ptr == nullptr
      */
      iterator() : ptr(nullptr) {}

      /**
        @brief Costruttore di copia

        Costruttore di copia per inizializzare un iterator uguale a &other

        @param &other iterator da copiare
        @post ptr == other.ptr
      */
      iterator(const iterator &other) : ptr(other.ptr) {}

      /**
        @brief Operatore di assegnamento

        Operatore di assegnamento che serve per copiare il contenuto di
        other in *this.

        @param &other iterator da copiare
        @return reference
      */
      iterator& operator=(const iterator &other) {
        ptr = other.ptr;
        return *this;
      }

      /**
        @brief Distruttore della classe

        Distruttore della classe, il distruttore di default va bene
      */
      ~iterator() {

      }

      /**
        @brief Operatore di deferenziamento

        Ritorna il dato riferito dall'iterare

        @return *ptr reference dell'iteratore
      */
      reference operator*() const {
        return *ptr;
      }

      /**
        @brief Operatore di puntamento

        Ritorna il puntatore al dato

        @return ptr puntatore del dato
      */
      pointer operator->() const {
        return ptr;
      }

      /**
        @brief Operatore di post-incremento

        Passa al prossimo iteratore dopo aver ritornato l'iterare

        @return tmp file temp uguale a *this prima di essere incrementato
      */
      iterator operator++(int) {
        iterator tmp(*this);
        --ptr;
        return tmp;
      }

      /**
        @brief Operatore di pre-incremento

        Passa al prossimo iteratore e lo ritorno

        @return *this ritorna il prossimo iteratore
      */
      iterator& operator++() {
        --ptr;
        return *this;
      }

      /**
        @brief Operatore di uguaglianza

        Operatore di uguaglianza che serve per indicare se other.ptr è
          uguale da this->ptr

        @param &other Stack da controllare passato come reference
        @return boolean che indica l'uguaglianza o meno tra other e this
      */
      bool operator==(const iterator &other) const {
        return (ptr == other.ptr);
      }

      /**
        @brief Operatore di disuguaglianza

        Operatore di disuguaglianza che serve per indicare se other.ptr è
          diverso da this->ptr

        @param &other Stack da controllare passato come reference
        @return boolean che indica la disuguaglianza o meno tra other e this
      */
      bool operator!=(const iterator &other) const {
        return (ptr != other.ptr);
      }

    private:
      //Dati membro

      friend class Stack;

      /**
        @brief Costruttore privato di inizializzazione

        Costruttore privato di inizializzazione usato dalla classe container

        @param *p puntadore a Stack costanti

        @post ptr = p
      */
      iterator(T* p) : ptr(p) { }

    };// iterator

    /**
      @brief Costruttore secondario #2

      Costruttore che crea un _stack prendendo gli elementi attraverso gli iteratori
      begine e end

      @param begin iterator che indica l'inizio della sequenza di dati
      @param end iterator che indica la fine della sequenza di dati

      @post _stack viene inizializzato sull'heap
    */
    Stack(iterator begin, iterator end) : _stack(nullptr), _size(0){
      iterator it, ite;
      for (it=begin, ite=end; it != ite; it++) {
        push(*it);
      }

      #ifndef NDEBUG
      std::cout << "Stack::Stack(iterator begin, iterator end)" << std::endl;
      #endif
    }
    /**
      @brief Metodo di begin

      Ritorna l'iteratore all'inizio della sequenza dati

      @return iterator primo iteratore
      */
    iterator begin() const {
       return iterator(_stack + _size - 1);
    }

    /**
      @brief Metodo di end

      Ritorna l'iteratore alla fine della sequenza dati

      @return iterator ultimo iteratore
      */
    iterator end() const {
       return iterator(_stack - 1);
    }

  public:
    /**
      @brief Metodo fill

      Metodo che riempie lo stack con la sequenza di dati che iniziz da begin
      e termina con end, se stack è già vuoto, altrimenti prima lo svuota

      @param begin iterator che indica l'inizio della sequenza di dati
      @param end iterator che indica la fine della sequenza di dati

      @post _stack viene inizializzato sull'heap
    */
    void fill(iterator begin, iterator end){
      if(_size != 0){
        delete[] _stack;
        _stack = nullptr;
        _size = 0;
      }

      iterator it, ite;
      for (it=begin, ite=end; it != ite; it++) {
        push(*it);
      }
    }
    /**
      @brief Metodo removeif

      Metodo che elimina tutti gli elementi dell stack che soddisfano il predicato
      passato in input

      @param pr Pred predicato generico

      @post elimina dallo stack gli elementi che soddisfano pr
      @post _size = _size - n dove n è il numero di elementi eliminati
    */
    template<class Pred>
    void removeif(Pred pr){
      if(_size == 0){
        throw "Stack is empty";
      }
      int n = 0;
      value_type* copy_stack;

      copy_stack = new value_type[_size];

      try {
        for(size_type i=0, j=0; j < _size; j++)
          if(pr(_stack[j])){
            n++;
          } else{
              copy_stack[i] = _stack[j];
              i++;
            }
      }
      catch(...) {
        delete[] copy_stack;
        copy_stack = nullptr;
        throw;
      }

      delete[] _stack;
      _stack = nullptr;
      _size = _size - n;

      _stack = new value_type[_size];

      try {
        for(size_type i=0; i < _size; ++i)
          _stack[i] = copy_stack[i];
      }
      catch(...) {
        delete[] _stack;
        _stack = nullptr;
        _size = 0;
        throw;
      }

      delete[] copy_stack;
      copy_stack = nullptr;
    }

  };// Stack

  /**
    @brief ridefinizione operatore di stream di Stack

    Ridefinizione dell'operatore di stream per scrivere uno
    Stack su uno stream di output

    @param os stream di output
    @param &st Stack da scrivere

    @return reference allo stream di output
  */
  template <typename U>
  std::ostream& operator<<(std::ostream &os, const Stack<U> &st) {
    os << st.size() << std::endl;
    for(typename Stack<U>::size_type i = 0; i < st.size(); ++i)
      os << st.value(i) << " ";
    os << std::endl;

    return os;
  };

  /**
    @brief Struct usata per test

    Definizione della struct Punto
  */
  struct Punto{
    double x; ///< X
    double y; ///< Y

    /**
      @brief Costruttore di default

      Costruttore di default della struct punto che mette x e y a 0.0

      @post x = 0.0
      @post y = 0.0
    */
    Punto(void);

    /**
      @brief Costruttore secondario

      Costruttore secondario della struct punto che mette x e y a xx e yy

      @post x = xx
      @post y = yy
    */
    Punto(double xx, double yy);

    /**
      @brief Operatore di uguaglianza

      Operatore di uguaglianza che serve per indicare se &p2 è uguale a this

      @param p2 Nodo da controllare
      @return boolean che indica l'uguaglianza o meno tra p2 e this
    */
    bool operator==(const Punto &p2);

  };

#endif
