---
name: Task template
about: This is a template for creating tasks for team members.
title: ''
labels: ''
assignees: ''

---

# Task title

## Context

Here describe the context of this tasks. Why do you want to open this task? Why should it be completed? How completing it will contribute to the project?

_Example_

> The frontend and the backend need an effective way to communicate with each other. A message queue is well suited for this. It allows for easy task distribution and is straightforward to use.

## Problem statement

Here describe what exactly needs to be done. The task must be clearly worded and realistic.

Be careful here. Describe **precisely** what you want to be done. Think of it like the assignee has an irresistible desire to do everything you did not put here in the exact opposite way compared to what you want (just to irritate you, for fun). Try to think of everything that can go wrong, just in case.

_Example_

> A class `MessageQueue` must be implemented. It must have two methods:
> * `void push(Request request);`
> * `Request pop();`
> The first one should add the request to the queue. The second is to delete the first of the remaining ones and return it.
>
> For this task one must create a separate branch based on the latest commit of branch [base branch].
>
> The implementation must be split across two files located at the following paths:
> `rediska/common/queue/MessageQueue.hpp` - the declarations for the class
> `rediska/common/queue/MessageQueue.cpp` - the definitions for the class
>
> Tests for the class must also be added. The following cases must be covered:
> 1. Case 1
> 2. Case 2
>
> After the task is completed, a pull request to [base branch] must be created and [requester's name] must be added as the assignee.

## Success criteria

List all conditions that can be objectively verified and unambiguously indicate successful completion of the task.

_Example_

> 1. The aforementioned class with the requested interface is implemented, the implementation can be found at path [path].
> 2. Unit tests, which cover all of the listed cases, are added and the implementation passes all of them.

## Advice (optional)

If you still have anything helpful to add, do it here. Provide any advice that will help the assignee quickly and successfully complete the task. _Do not hesitate to think for them a little, if you believe it will help them do their job more effectively (in a shorter time period without prejudice to correctness)_.
