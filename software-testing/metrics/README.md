# Metrics

<!-- markdown-toc start - Don't edit this section. Run M-x markdown-toc-refresh-toc -->
**Table of Contents**

- [Metrics](#metrics)
    - [Testing metric](#testing-metric)
        - [Coverage metrics](#coverage-metrics)
    - [Mutation analysis](#mutation-analysis)
    - [Design and code metrics](#design-and-code-metrics)
        - [Code size](#code-size)
            - [Comment lines](#comment-lines)
    - [Halsteads software science metrics](#halsteads-software-science-metrics)
    - [OO design metrics](#oo-design-metrics)
        - [Weighted methods per class (WMC)](#weighted-methods-per-class-wmc)
            - [Complexities for a method](#complexities-for-a-method)
    - [Depth of inheritance -DIT](#depth-of-inheritance--dit)
    - [Number of children - NOC](#number-of-children---noc)
    - [Coupling between objects - CBO](#coupling-between-objects---cbo)
    - [Response for a class - RFC](#response-for-a-class---rfc)
    - [Lack of cohesion in methods (LCOM)](#lack-of-cohesion-in-methods-lcom)
        - [If they share no instance variables](#if-they-share-no-instance-variables)
        - [LCOM](#lcom)
    - [Fault prediction](#fault-prediction)
        - [Model generator](#model-generator)
        - [Maintainability](#maintainability)
    - [The only metric that seems like a useful predictor of maintenance effort is... lines of code!](#the-only-metric-that-seems-like-a-useful-predictor-of-maintenance-effort-is-lines-of-code)
    - [RULE OF THUMB: BYO models](#rule-of-thumb-byo-models)
        - [Watch out for red flags](#watch-out-for-red-flags)
    - [Traps and statics TODO](#traps-and-statics-todo)
    - [Taylorism](#taylorism)

<!-- markdown-toc end -->

## Testing metric
### Coverage metrics
* Can compute statement and branch coverage
* MC/DC coverage are available for the kinds of languages in which safety-critical automotive and aerospace code is written
* Code coverage is easy to compute and useful indicator of test suit quality.
* There is *no reliable industry model* that can tell you "x% coverage is sufficient to give you reliability".
* **specification coverage** should somewhere around 100%

## Mutation analysis
* Involves automatically seeding a change in your code.
* Mutation score varies between 0 to 1.
* Better indication whether your test suite is any good than just code coverage.
* Can be problematic if **generating thousands of mutants and running the test suite on each of them**

## Design and code metrics
Statically analysing source code and in some cases uml diagrams
* Good indicator of **functional correctness** and potentially useful proxies for the maintainability and **portability of software**.

### Code size
* Determine how big it is.
* lines of code (LOC). This very easy to measure

#### Comment lines
Are useful and often when there are a lot of comment lines it indicates that the code itself is harder to understand <br />
Are quicker to write compared to code itself <br />
**LOC counters** provide more detailed counts, tabulating comments and blank lines separately. <br />
Larger methods are much more error-prone than small methods.

## Halsteads software science metrics
HSCM can predict the difficulty, effort required and likely correctness of code.

## OO design metrics
The more interactions and complex the interactions are between modules and classes, the harder code is to write and debug More interactions between classes means more mocking for unit testing, more tracing faults down through many different classes.

### Weighted methods per class (WMC)
For class with methods M_1, M_2 up to M_n. 
Complexities of each method: c_1, c_2, c_n. <br />
![Alt Text](pic1.png) 

#### Complexities for a method
There are a number of ways  already discussed and Chdiamber and Kemerer deliberately did not refine this. <br />
The complexity of a method is likely to be application specific due to different programming languages and different definitions of operands and operators.
The complexity metric **requires code to measure**. 

## Depth of inheritance - DIT
The depth or inheritance it takes to reach to the class of the inheritance tree.
![Alt Text](pic2.png)
DIT for <kbd>VerticalLayout</kbd> is 3 and DIT for object is 0.
A higher DIT number was thought to make designs more complex. This is because the class at the bottom of the hierarchy inherits more and more properties, but a higher DIT also implies more reuse (which is considered good.)

## Number of children - NOC
![Alt Text](pic2.png)
Widget has three children
Object has 1 children
Leaf nodes like VerticalLayout have zero children
High NOC indicates reuse (good) but also indicates inappropriate abstraction (bad). Classes with **high number of children were thought to require more testing, because high influence over large parts of the design is heavily used**.

## Coupling between objects - CBO
The number of other classes it interacts with directly. High coupling is bad because becomes harder to design, build, test debug, extend and reuse classes. CBO metric is reasonable measure for coupling and a high CBO number for classes is bad. More arrows between a class and other classes indicate high CBO

## Response for a class - RFC
All the methods in C and all the methods invoked directly by methods in C.
You do not need to worry about the methods invoked in the methods invoked by C (not transitive)

## Lack of cohesion in methods (LCOM)
The closeness of the relationships between the elements of the same module.
Cohesion, functional cohesion, occurs when a single clear and unambiguous purpose.
Methods: {M_1, M_2, M_n}
Instance variables a methods operates on: {I_j}
For **each pair** determine if any of the instance variables they operate on are the same. (That is, I_a and I-b contain at least one shared element)
Low cohesion as measured by this metric was believed by Chidamber and Kemerer tto lead to code that is less easy to **test, debug, maintain and resuse**,.

### If they share no instance variables
Add 1 to P, otherwise add 1 to Q.

### LCOM
    LCOM = P - Q, P > Q otherwise.

## Fault prediction

### Model generator
Academics tend to use machine learning techniques (Big data). This involves feed data into the model by "training it**

Pointers to what modules to test more intensively.

**Predicting** future software defects so practitioners can effectively optimise limited resources.
**Explaining** what makes a software fail so managers can develop the most effective improvement plans.
**Building** empirical grounded theories of software quality

There are different types of fault prediction metrics:

* Static source code measures, like the ones we have been discussing
* Software process metrics such as the number of bugs already found in the modules.
* Personnel-based information such as who has been working on the modules.

> "...On the other hand, models using only static code metrics (typically complexity based) perform relatively poorly. Model performance does not seem to be improved by combining these metrics with OO metrics. Models seem to perform better using only OO metrics rather than only source code metrics. However, models using only LOC seem to perform just as well as those using only OO metrics and better than those models only using source code metrics." <br />

### Maintainability

Ability to maintain and extend the code we write.

Furthermore, they found this relationship was a useful rule of thumb for individual modules, not just whole systems made up of many modules:

> The figure shows that 364 files, or roughly 50 percent of the system, fall below the quality-cutoff index, strongly suggesting that this system is difficult to modify and maintain. Prior to our analysis, the HP maintenance engineers had stated that the system was very difficult to maintain and modify. Further analysis proved of - 91. Table 3. A polynomial comparison of two systems corroborated an informal evaluation by engineers. A that change-prone and defect-prone subsystem components (files) could be targeted using the ranked order of the maintainability indices.  <br />


* Do developer's perceptions of maintainability relate to **actual quantifiable maintenance**
* properties - in a business context, does it relate to time/cost to maintain? 

* Does **a metric originally devised based on C code decades ago still apply to code written in OO languages such as Java, Python and so on**?


## The only metric that seems like a useful predictor of maintenance effort is... lines of code!

![Alt Text](pic4.png) 

> It is possible that **metrics apart from size** may play a role in reducing maintenance effort in large projects where it takes a long time (> 3 years) for developers to become fluent [19], but we see no evidence that they matter in our context.

While the individual studies they examined indicated that a broad range of metrics were somehow connected with maintainability (they found that the most successful predictors related to "**size, complexity and coupling**") they concluded that the results were not convincing enough for broad applicability

## RULE OF THUMB: BYO models

### Watch out for red flags
For instance, the maintainability indices of the four systems shown in figure 3 were around 120, the equivalent of about 70 on Microsoft's scale. That’s way, way above the 20 threshold that Microsoft uses as a "red flag".

"Red flag" on the maintainability index - are probably useful indicators of potential quality problems, including correctness and maintainability. Observe that what this is likely to come down to is the presence of overly large methods! Similarly, indications of **overly close coupling between classes are likely indicative of a design problem** and is something you can probably spot at the design stage.

Even though it might be difficult to make general recommendations from metrics, they can still be worth measuring and recording.

Collecting metrics using automated tools from source code is an **extremely cheap process**. If you do that across a large project, or multiple projects in an organisation you can **look for your own patterns connecting particular "proxy metrics" with the things you ultimately want to achieve**.

* Number and severity of failures reported after release.
* Time required to fix bugs.
* Time required to add new features.
* Number of code changes required to add new features.

## Traps and statics TODO

## Taylorism

Taylorism
The idea of managing the behaviour of workers producing something by systematic measurement (measure everything). Many of the principles espoused in it are echoed in software engineering today, particularly the more **rigid, process-oriented types**. In short, Taylor espoused the following:

* Based on empirical measurement, develop a detailed "science" for each worker's job - essentially, a **manual describing in detail exactly how they should do their work as efficiently as possible**.

* "Scientifically" choose the best people for the job, and **train them fully in the methodology**. Work with employees to ensure that they follow this "scientific" process precisely. This would involve incentivising them to a) follow the process, and b) **rewarding them for maximising the management's desired outputs**, which must be numerically measurable.

* Take all of the thinking out of the worker's job and hand it to management.

Measuring desirable outputs is not always so easy. For instance, consider this little anecdote, where the desired output is not enough due to **Goldberg effect and perverse incentives**. **Metrics should not be a goal**.

![Alt Text](pic5.png) 

## Code review metrics
* Measure the activities in project (commits in git)
* Coverage of the code review
    * Proportion of changes that have been reviewed in the past.
    * Proportion of code that has been reviewed in the past.
* Code review participation
    * #Self-Approved: The proportion of changes to the file that are only approved for integration by the original author (Maybe bad?)
* Code review ownership
    * The number of developers who have reviewed code changes to the file
    * The degree of review ownership
* Pull request
* Merge requests
