type action = 
  | AddItem(string)
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
        />
        (str(item.title))
      </div>
  };
};

let valueFromEvent = (evt) : string => (
  evt
  |> ReactEventRe.Form.target
  |> ReactDOMRe.domElementToObj
)##value;


module Input = {
  type state = string;
  let component = ReasonReact.reducerComponent("input");
  let make = (~onSubmit, _) => {
    ...component,
    initialState: () => "",
    reducer: (newText, _text) => ReasonReact.Update(newText),
    render: ({state: text, reduce}) => 
      <input
        value=text
        _type="text"
        placeholder="Write something to do"
        onChange=(reduce((evt) => valueFromEvent(evt)))
        onKeyDown=((evt) =>
          if (ReactEventRe.Keyboard.key(evt) == "Enter") {
            onSubmit(text);
            (reduce(() => ""))()
          })
        />
  };
};

type state = {
  items: list(item)
};

let component = ReasonReact.reducerComponent("ToDoApp");

let lastId = ref(0);

let newItem = (text) => {
  lastId := lastId^ + 1;

  {id: lastId^, title: text, completed: false};
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
      | AddItem(text) => ReasonReact.Update({items: [newItem(text), ...items]})
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
        <Input onSubmit=(reduce((text) => AddItem(text))) />
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