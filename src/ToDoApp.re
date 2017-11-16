type action = 
  | AddItem;

type item = {
  title: string,
  completed: bool
};

type state = {
  items: list(item)
};

let component = ReasonReact.reducerComponent("ToDoApp");

let newItem = () => {title: "Click a Button", completed: true};

let str = ReasonReact.stringToElement;

let make = (_children) => {
    ...component,

    initialState: () => {
      items: [
        {title: "write some things to do", completed: false }
      ]
    },

    reducer: (action, {items}) => 
      switch action {
      | AddItem => ReasonReact.Update({items: [newItem(), ...items]})
      },

    render: ({state: {items}, reduce}) => {

      let numItems = List.length(items);

      <div className="app">
        <div className="title"> (str("What to do")) </div>
        <button onClick=(reduce((_evt) => AddItem))>
          (str("Add Something"))
        </button>
        <div className="items"> (str("Nothing")) </div>
        <div className="footer">
          (str(string_of_int(numItems) ++ " items"))
        </div>
      </div>
    }
};