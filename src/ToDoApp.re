type action = 
  | AddItem
  | ToggleItem(int);

type item = {
  id: int,
  title: string,
  completed: bool
};

let str = ReasonReact.stringToElement;

module TodoItem = {
  let component = ReasonReact.statelessComponent("TodoItem");
  let make = (~item, ~onToggle, _children) => {
    ...component,
    render: (_self) => 
      <div className="item" onClick=((_evt) => onToggle())>
        <input 
          _type="checkbox" 
          checked=(Js.Boolean.to_js_boolean(item.completed))
          /*TODO make interactive*/
        />
        (str(item.title))
      </div>
  };
};

type state = {
  items: list(item)
};

let component = ReasonReact.reducerComponent("ToDoApp");

let lastId = ref(0);

let newItem = () => {
  lastId := lastId^ + 1;

  {id: lastId^, title: "Click a Button", completed: true};
};

let make = (_children) => {
    ...component, 

    initialState: () => {
      items: [
        {id: 0, title: "write some things to do", completed: false }
      ]
    },

    reducer: (action, {items}) => 
      switch action {
      | AddItem => ReasonReact.Update({items: [newItem(), ...items]})
      | ToggleItem(id) =>
          let items = List.map(
            (item) =>
              item.id === id ? {...item, completed: ! item.completed } : item,
            items
          );
          ReasonReact.Update({items: items})
      },

    render: ({state: {items}, reduce}) => {

      let numItems = List.length(items);

      <div className="app">
        <div className="title"> (str("What to do")) </div>
        <button onClick=(reduce((_evt) => AddItem))>
          (str("Add Something"))
        </button>
        <div className="items"> (
          ReasonReact.arrayToElement(Array.of_list(
            List.map(
              (item) => 
                <TodoItem 
                  key=(string_of_int(item.id))
                  onToggle=(reduce(() => ToggleItem(item.id))) 
                  item 
                />, items
            )
          )))
        </div>
        <div className="footer">
          (str(string_of_int(numItems) ++ " items"))
        </div>
      </div>
    }
};