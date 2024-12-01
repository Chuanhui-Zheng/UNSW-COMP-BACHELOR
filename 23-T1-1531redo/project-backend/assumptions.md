General Assumptions:

==  Registered users are required to log in before any further operation request.
------------------------------------
==  Any incorrect types of inputs taken by functions, will cause an {error : 'error'} return.
------------------------------------
==  AuthUserIds in functions are supposed to be always non-negative Number type in JS, otherwise will be considered as invalid input.
------------------------------------
==  All emails that users use for registration, will be in format '***@***.com', otherwise will be considered as invalid input.
------------------------------------
==  Messages are supposed to be ascending ordered in arrays, i.e. according to timeSent from the newest to oldest.
------------------------------------
==  Function channelMessages, argument 'start' is supposed to be non-negative Number type, if not return {error : 'error'}.

