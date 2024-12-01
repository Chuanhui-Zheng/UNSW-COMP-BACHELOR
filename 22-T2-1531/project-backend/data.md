```javascript
let data = {
  users: [
    {
      uId: 1,
      nameFirst: 'Richard',
      nameLast: 'Lee',
      email: 'RichardLee@gmail.com',
      handleStr: 'ricki',
      password: 'abcdefg',
    },
  ],

  channels: [
    {
      channelId: 1,
      name: 'My Channel',
      isPublic: false,
      ownerMemberIds: [1],
      allMemberIds: [1],
      messages: [
        {
          uId: 1,
          messageId: 1,
          message: 'Hello World',
          timeSent: 12345678,
        },                
      ],
      start: 0,
      end: 50,
    },
  ],
};
```

[Optional] short description: 
We've used the combination of output types and the stub return values to integrate into our current data type. Also, we have 
used lists for users and channels to allow easy manipulation, for example adding and removing information and objects.

